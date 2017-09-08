

#include <stdio.h>
#include <unistd.h>   
#include <sys/types.h>   
#include <fcntl.h>   
#include <sys/stat.h>   
#include <stdio.h> 
#include <string.h>   
#include <sys/param.h>   
#include <sys/ioctl.h>   
#include <stdlib.h>   
#include <stdio.h>
#include <iostream> 
#include <sys/socket.h>   
#include <arpa/inet.h> 
#include "sys/select.h"   
#include "termios.h"

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtCore/QSettings>

#include "KSJSCZDemoMainWindow.h" 
#include "ui_KSJSCZDemoMainWindow.h"

#include "../ksjsczapi_include/KSJSczApiShow.h"
#include "../ksjsczapi_include/KSJSCZApiBase.h"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"
#include "../ksjsczapi_include/KSJSCZApiIo.h"
#include "../ksjsczapi_include/KSJSczApiCode.h"
#include "../ksjsczapi_include/KSJSczApiInternal.h"
#include "../ksjsczapi_include/KSJSczApiUser.h"

#define  DEFAULT_WND_WIDTH  960
#define  DEFAULT_WND_HEIGHT 720


// 中断驱动文件 系统预留给用户的中断
#define DEVICE_INTERRUPT_FILE "ksj_feedback_0"



// 等待中断程序，可以放到一个线程里面去
bool WaitIpInterrupt(unsigned int nTimeoutMS)
{
	bool bInterrupted = false;

	// 打开中断驱动文件
	int nFdInterrupt = open(DEVICE_INTERRUPT_FILE, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (nFdInterrupt == -1) return bInterrupted;

	fd_set fsRead;
	struct timeval timeout;

	// 设置等待的时间
	timeout.tv_sec = nTimeoutMS / 1000;
	timeout.tv_usec = nTimeoutMS % 1000 * 1000;

	FD_ZERO(&fsRead);
	FD_SET(nFdInterrupt, &fsRead);

	// 打开中断驱动文件
	int nSelRet = select(nFdInterrupt + 1, &fsRead, NULL, NULL, &timeout);

	if ((nSelRet > 0) && FD_ISSET(nFdInterrupt, &fsRead))
	{
		// 如果等到中断，可以读取文件查看返回中断的内容
		/*
		char szBuffer[9] = { 0 };
		int nLen = read(nFdInterrupt, szBuffer, 8);

		if (nLen > 0)
		{
			// 用szBuffer分别与， "33" "34" "35" "36" "37" "38" 作比较，可以知道返回中断的序号
		}
		*/
		bInterrupted = true;
	}

	close(nFdInterrupt);

	return bInterrupted;
}

// 图像采集线程
void* ThreadForCaptureData(void *arg)
{
	if (NULL == arg)
	{
		pthread_exit((char*)"ThreadForSignalMode");
	}

	CKSJSCZDemoMainWindow* pMainWindow = (CKSJSCZDemoMainWindow*)arg;

	pMainWindow->update();

	while (!pMainWindow->m_bStopCaptureThread)
	{
		if (pMainWindow->m_bIsCapturing)
		{
			int nWidth, nHeight, nBitCount;

			KSJSCZ_GetCaptureSize(0, &nWidth, &nHeight, &nBitCount);

			unsigned char *pImageData = NULL;

			// 采集图像
			if (KSJSCZ_ERR_SUCCESS == KSJSCZ_CaptureData(0, &pImageData))
			{
				// 处理图像
				pMainWindow->CaptureData(pImageData, nWidth, nHeight, nBitCount);
				KSJSCZ_ReleaseBuffer(0);
			}
		}
		else
		{
			usleep(1000);
		}
	}

	pthread_exit(0);

	return ((void *)0);
}


CKSJSCZDemoMainWindow::CKSJSCZDemoMainWindow(QWidget *parent) :
QDialog(parent)
, ui(new Ui::KSJSCZDemoMainWindow)
, m_bIsCapturing(false)
, m_bStopCaptureThread(false)
, m_nCaptureInterruptThreadId(0)
, m_nImageWidth(0)
, m_nImageHeight(0)
, m_nImageBitCount(0)
, m_nThresholdValue(128)
, m_bFastXImage(true)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->StopCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStopCapture()));
	connect(ui->ThresholdCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnThresholdChkBoxStateChanged(int)));
	connect(ui->ExpLinesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnExpLinesChanged(int)));
	connect(ui->ScobelPushButton, SIGNAL(clicked()), this, SLOT(OnScobelInFpga()));
	connect(ui->FastXThreshold, SIGNAL(valueChanged(int)), this, SLOT(OnThresholdValueChanged(int)));

	ui->FastXThreshold->blockSignals(true);
	ui->FastXThreshold->setValue(m_nThresholdValue);
	ui->FastXThreshold->blockSignals(false);

	ui->ThresholdCheckBox->blockSignals(true);
	ui->ThresholdCheckBox->setCheckState(m_bFastXImage ? Qt::Checked : Qt::Unchecked);
	ui->ThresholdCheckBox->blockSignals(false);

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);

	int nRet = KSJSCZ_Init();
	
	m_nVideoMemorySize = 1280 * 1024 * 3;

	// 分配一个用于显示的内存
	if (KSJSCZ_Malloc(m_nVideoMemorySize, &m_pVideoMemory) != KSJSCZ_ERR_SUCCESS)
	{
		m_pVideoMemory = NULL;
		m_nVideoMemorySize = 0;
	}
	
	// 分配一个临时内存区
	KSJSCZ_Malloc(m_nVideoMemorySize, &m_pTempMemory);

	nRet = KSJSCZ_SetGain(0, 128);
	//nRet = KSJSCZ_SetExposureLines(0, 500);

	nRet = KSJSCZ_SetVideoWidgetPos(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetPosition(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, (1280-960)/2, (1024-720)/2, 960, 720);

	unsigned long ulValue, ulValueMin, ulValueMax;

	KSJSCZ_GetExposureLines(0, &ulValue);
	KSJSCZ_GetExposureLinesRange(0, &ulValueMin, &ulValueMax);
	ui->ExpLinesSpinBox->blockSignals(true);
	ui->ExpLinesSpinBox->setRange(ulValueMin > 2 ? ulValueMin : 2, ulValueMax);
	if (ulValue > 2000) ulValue = 2;
	ui->ExpLinesSpinBox->setValue(ulValue);
	KSJSCZ_SetExposureLines(0, ulValue);
	ui->ExpLinesSpinBox->blockSignals(false);

	KSJSCZ_SetUsingMultiShowBuffer(0, false);
	KSJSCZ_SetTriggerMode(0, KSJSCZ_TM_CMD_CONTINUE);

	StartCaptureThread();
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	KillCaptureThread();

	if (m_pVideoMemory != NULL)
	{
		KSJSCZ_Free(&m_pVideoMemory);
		m_nVideoMemorySize = 0;
	}

	if (m_pTempMemory != NULL)
	{
		KSJSCZ_Free(&m_pTempMemory);
	}

	KSJSCZ_UnInit();

	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.setPen(Qt::NoPen);

	painter.setBrush(Qt::black);
	painter.drawRect(QRect(0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT));
}

int CKSJSCZDemoMainWindow::StartCaptureThread()
{
	int nRet = KSJSCZ_ERR_ERROR;

	m_bStopCaptureThread = false;

	pthread_attr_t  attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	nRet = pthread_create(&m_nCaptureInterruptThreadId, &attr, ThreadForCaptureData, (void *)this);
	pthread_attr_destroy(&attr);

	if (nRet != 0)
	{
		nRet = KSJSCZ_ERR_ERROR;
	}
	else
	{
		nRet = KSJSCZ_ERR_SUCCESS;
	}

	return nRet;
}

int CKSJSCZDemoMainWindow::KillCaptureThread()
{
	m_bStopCaptureThread = true;
	return KSJSCZ_ERR_SUCCESS;
}

void CKSJSCZDemoMainWindow::OnStartCapture()
{
	m_bIsCapturing = true;

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);
}

void CKSJSCZDemoMainWindow::OnScobelInFpga()
{
	KSJSCZ_WrRegFPGA(0, 0x94, 0x00100000);
}

void CKSJSCZDemoMainWindow::OnStopCapture()
{
	m_bIsCapturing = false;

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);
}

void CKSJSCZDemoMainWindow::CaptureData(unsigned char* pImage, int w, int h, int bitcount)
{
	m_nImageWidth = w;
	m_nImageHeight = h;
	m_nImageBitCount = bitcount;

	if (m_nVideoMemorySize < (w*h*bitcount/8))
	{
		if (m_pVideoMemory != NULL)
		{
			KSJSCZ_Free(&m_pTempMemory);
			KSJSCZ_Free(&m_pVideoMemory);
			m_nVideoMemorySize = 0;
		}

		m_nVideoMemorySize = w*h*bitcount/8;

		if (KSJSCZ_Malloc(m_nVideoMemorySize, &m_pVideoMemory) != KSJSCZ_ERR_SUCCESS)
		{
			m_pVideoMemory = NULL;
			m_nVideoMemorySize = 0;
		}
		
		KSJSCZ_Malloc(m_nVideoMemorySize, &m_pTempMemory);
	}

	if (m_pVideoMemory != NULL)
	{
		if (m_bFastXImage)
		{
			memcpy(m_pTempMemory, pImage, w*h);
			
			// 设置输入参数
			KSJSCZ_WrRegUserVDMA(0, 0, 4);
			KSJSCZ_WrRegUserVDMA(0, 0, 8);
			KSJSCZ_WrRegUserVDMADataAddr(0, 0x5c, m_pTempMemory);
			KSJSCZ_WrRegUserVDMA(0, 0x54, m_nImageWidth);
			KSJSCZ_WrRegUserVDMA(0, 0x58, m_nImageWidth);
			KSJSCZ_WrRegUserVDMA(0, 0, 0x0b);
			KSJSCZ_WrRegUserVDMA(0, 0x50, m_nImageHeight);
			// 设置输出参数
			KSJSCZ_WrRegUserVDMA(0, 0x30, 4);
			KSJSCZ_WrRegUserVDMA(0, 0x30, 8);
			KSJSCZ_WrRegUserVDMADataAddr(0, 0xac, m_pVideoMemory);
			KSJSCZ_WrRegUserVDMA(0, 0xa4, m_nImageWidth);
			KSJSCZ_WrRegUserVDMA(0, 0xa8, m_nImageWidth);
			KSJSCZ_WrRegUserVDMA(0, 0x30, 0x1017003);        // 设置成中断模式
			KSJSCZ_WrRegUserVDMA(0, 0xa0, m_nImageHeight);
			// 设置FastX参数
			KSJSCZ_WrUserRegFPGA(0xB4, m_nThresholdValue);

			//* 消中断标志
			KSJSCZ_WrRegUserVDMA(0, 0x34, 0x1000);

			// 触发运算
			KSJSCZ_WrUserRegFPGA(0x94,0x00010000);

			if (WaitIpInterrupt(5))   // 等待中断5MS
			{
				printf(" ==== OK ====\r\n");
			}
			else
			{
				printf(" ==== Time out ====\r\n");
			}
		}
		else
		{
			memcpy(m_pVideoMemory, pImage, w*h);
		}	

		KSJSCZ_ShowUserLoadData(0, m_pVideoMemory, m_nImageWidth, m_nImageHeight, m_nImageBitCount);
	}
}


void CKSJSCZDemoMainWindow::mousePressEvent(QMouseEvent * e)
{
}

void CKSJSCZDemoMainWindow::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
	}
}

void CKSJSCZDemoMainWindow::mouseMoveEvent(QMouseEvent * e)
{
	if (e->pos().y() <= 960)
	{
		ui->InfoLabel->setText("Position: (" + QString::number(e->pos().x()) + "," + QString::number(e->pos().y()) + ")");
	}
}

void CKSJSCZDemoMainWindow::mouseDoubleClickEvent(QMouseEvent * e)
{
}

void CKSJSCZDemoMainWindow::wheelEvent(QWheelEvent * event)
{
}

void CKSJSCZDemoMainWindow::OnThresholdChkBoxStateChanged(int value)
{
	m_bFastXImage = (value == Qt::Checked);
}

void CKSJSCZDemoMainWindow::OnExpLinesChanged(int value)
{
	KSJSCZ_SetExposureLines(0, value);
}

void CKSJSCZDemoMainWindow::OnThresholdValueChanged(int nValue)
{
	m_nThresholdValue = ui->FastXThreshold->value();
}
