

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

#include <unistd.h>   
#include <sys/types.h>   
#include <fcntl.h>   
#include <sys/stat.h>   
#include <stdio.h>   
#include <sys/param.h>   
#include <sys/ioctl.h>   
#include <stdlib.h>   
#include <stdio.h>
#include <iostream> 
#include <sys/socket.h>   
#include <arpa/inet.h>   
#include <linux/soundcard.h>   
#include "sys/select.h"   
#include "termios.h" 
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
			pMainWindow->update();
			usleep(10000);
		}
		else
		{
			usleep(100000);
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
, m_nImageWidth(1280)
, m_nImageHeight(720)
, m_nImageBitCount(24)
, m_nImageLastWidth(-1)
, m_nImageLastHeight(-1)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);

	m_pImageZoomer = new CKSJVBImageZoom();

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->StopCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStopCapture()));

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);

	m_rcClient.setRect(0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	m_pImageZoomer->SetClientSize(DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);

	int nRet = KSJSCZ_Init();
	
	m_nVideoMemorySize = m_nImageWidth * 720 * 3;

	if (KSJSCZ_Malloc(m_nVideoMemorySize, &m_pVideoMemory) != KSJSCZ_ERR_SUCCESS)
	{
		m_pVideoMemory = NULL;
		m_nVideoMemorySize = 0;
	}

	int i, j;

	memset(m_pVideoMemory, 0, m_nImageWidth*m_nImageHeight * 3);

	j = 0;

	for (; j < 1 * m_nImageHeight / 4; ++j)
	{
		for (i = 0; i < m_nImageWidth; ++i)
		{
			m_pVideoMemory[j * 3 * m_nImageWidth + 3 * i + 0] = 255;
		}
	}
	for (; j < 2 * m_nImageHeight / 4; ++j)
	{
		for (i = 0; i < m_nImageWidth; ++i)
		{
			m_pVideoMemory[j * 3 * m_nImageWidth + 3 * i + 1] = 255;
		}
	}
	for (; j < 3 * m_nImageHeight / 4; ++j)
	{
		for (i = 0; i < m_nImageWidth; ++i)
		{
			m_pVideoMemory[j * 3 * m_nImageWidth + 3 * i + 2] = 255;
		}
	}
	for (; j < 4 * m_nImageHeight / 4; ++j)
	{
		for (i = 0; i < m_nImageWidth; ++i)
		{
			m_pVideoMemory[j * 3 * m_nImageWidth + 3 * i + 0] = 255;
			m_pVideoMemory[j * 3 * m_nImageWidth + 3 * i + 1] = 255;
		}
	}

	KSJSCZ_HelperSaveToBmp(m_pVideoMemory, m_nImageWidth, m_nImageHeight, m_nImageBitCount, "/picture/data/demo_color.bmp");

	nRet = KSJSCZ_SetGain(0, 128);
	nRet = KSJSCZ_SetExposureLines(0, 500);

	nRet = KSJSCZ_SetVideoWidgetPos(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetPosition(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, 0, 0, 1280, 720);

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

	delete m_pImageZoomer;
	m_pImageZoomer = NULL;

	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.setPen(Qt::NoPen);

	painter.setBrush(Qt::black);
	painter.drawRect(QRect(0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT));

	if (m_pVideoMemory != NULL && m_nImageWidth > 0 && m_nImageHeight > 0 && m_nImageBitCount > 0)
	{
		if (m_nImageLastWidth != m_nImageWidth || m_nImageLastHeight != m_nImageHeight)
		{
			m_pImageZoomer->SetImageSize(m_nImageWidth, m_nImageHeight);

			m_nImageLastWidth = m_nImageWidth;
			m_nImageLastHeight = m_nImageHeight;
		}

		int nX, nY, nW, nH;
		m_pImageZoomer->GetImageShowPosition(nX, nY, nW, nH);

		KSJSCZ_SetPosition(0, nX, nY, nW, nH);

		printf("        %d-%d-%d-%d\r\n", nX, nY, nW, nH);

		KSJSCZ_ShowUserLoadData(0, m_pVideoMemory, m_nImageWidth, m_nImageHeight, m_nImageBitCount);
	}
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

void CKSJSCZDemoMainWindow::ZoomIn()
{
	ZoomIn(m_rcClient.width() / 2, m_rcClient.height() / 2);
}

void CKSJSCZDemoMainWindow::ZoomOut()
{
	ZoomOut(m_rcClient.width() / 2, m_rcClient.height() / 2);
}

void CKSJSCZDemoMainWindow::ZoomIn(int nClientX, int nClientY)
{
	if (m_pImageZoomer != NULL)
	{
		m_pImageZoomer->ZoomIn(nClientX, nClientY);

		this->update();
	}
}

void CKSJSCZDemoMainWindow::ZoomOut(int nClientX, int nClientY)
{
	if (m_pImageZoomer != NULL)
	{
		m_pImageZoomer->ZoomOut(nClientX, nClientY);

		this->update();
	}
}

void CKSJSCZDemoMainWindow::SetZoomMode(KSJ_ZOOM_MODE mode)
{
	if (m_pImageZoomer != NULL)
	{
		m_pImageZoomer->SetZoomMode(mode);

		this->update();
	}
}

void CKSJSCZDemoMainWindow::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_ptLastMouse = e->pos();
	}
}

void CKSJSCZDemoMainWindow::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
	}
}

void CKSJSCZDemoMainWindow::mouseMoveEvent(QMouseEvent * e)
{
	if (!(e->buttons()&Qt::RightButton) && (e->buttons() == Qt::LeftButton))
	{
		if (m_pImageZoomer != NULL)
		{
			m_pImageZoomer->Move(e->pos().x() - m_ptLastMouse.x(), e->pos().y() - m_ptLastMouse.y());

			update();
		}
	}

	m_ptLastMouse = e->pos();

	if (m_ptLastMouse.y()<=960)
	{
		ui->InfoLabel->setText("Position: (" + QString::number(m_ptLastMouse.x()) + "," + QString::number(m_ptLastMouse.y()) + ")");
	}
}

void CKSJSCZDemoMainWindow::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)   //ÓÒ¼üË«»÷
	{
		m_pImageZoomer->SetZoomMode(ZM_FITIMG);

		update();
	}
}

void CKSJSCZDemoMainWindow::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0)
	{
		ZoomIn(event->x(), event->y());
		update();
	}
	else
	{
		ZoomOut(event->x(), event->y());
		update();
	}
}

//ui->HorizontalScrollBar;
//ui->VerticalScrollBar;