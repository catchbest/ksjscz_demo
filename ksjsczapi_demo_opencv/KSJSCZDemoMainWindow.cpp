

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtCore/QSettings>

#include "KSJSCZDemoMainWindow.h"
#include <unistd.h>
#include <sys/time.h>
#include "ui_KSJSCZDemoMainWindow.h"

#include "../ksjsczapi_include/KSJSczApiShow.h"
#include "../ksjsczapi_include/KSJSCZApiBase.h"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"
#include "../ksjsczapi_include/KSJSCZApiIo.h"
#include "../ksjsczapi_include/KSJSczApiCode.h"
#include "../ksjsczapi_include/KSJSczApiInternal.h"

#define  DEFAULT_WND_WIDTH  960
#define  DEFAULT_WND_HEIGHT 720

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

			if (KSJSCZ_ERR_SUCCESS == KSJSCZ_CaptureData(0, &pImageData))
			{
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
, m_bThresholdImage(true)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->StopCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStopCapture()));
	connect(ui->ThresholdCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnThresholdChkBoxStateChanged(int)));

	ui->ThresholdCheckBox->setCheckState(m_bThresholdImage ? Qt::Checked : Qt::Unchecked);

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);

	int nRet = KSJSCZ_Init();
	
	m_nVideoMemorySize = 1280 * 1024 * 3;

	if (KSJSCZ_Malloc(m_nVideoMemorySize, &m_pVideoMemory) != KSJSCZ_ERR_SUCCESS)
	{
		m_pVideoMemory = NULL;
		m_nVideoMemorySize = 0;
	}

	nRet = KSJSCZ_SetGain(0, 128);
	nRet = KSJSCZ_SetExposureLines(0, 500);

	nRet = KSJSCZ_SetVideoWidgetPos(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetPosition(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, 0, 0, 1280, 1024);

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
			KSJSCZ_Free(&m_pVideoMemory);
			m_nVideoMemorySize = 0;
		}

		m_nVideoMemorySize = w*h*bitcount/8;

		if (KSJSCZ_Malloc(m_nVideoMemorySize, &m_pVideoMemory) != KSJSCZ_ERR_SUCCESS)
		{
			m_pVideoMemory = NULL;
			m_nVideoMemorySize = 0;
		}
	}

	if (m_pVideoMemory != NULL)
	{
		if (m_bThresholdImage)
		{
			cv::Mat image(h, w, CV_8UC1, pImage, w);
			cv::threshold(image, image, 128, 255, CV_THRESH_BINARY);
		}

		memcpy(m_pVideoMemory, pImage, w*h);

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
	m_bThresholdImage = (value == Qt::Checked);
}