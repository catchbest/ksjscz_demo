

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QScrollBar>
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
				pMainWindow->ConvertToQImage(pImageData, nWidth, nHeight);
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
, m_pImage(NULL)
, m_bIsCapturing(false)
, m_bStopCaptureThread(false)
, m_nCaptureInterruptThreadId(0)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	m_nShowWidth = 960-10;
	m_nShowHeight = 720-10;

	m_pImageShowLabel = new CImageLabel;
	m_pImageWidgetScroll = new QScrollArea(this);
	m_pImageWidgetScroll->setWidget(m_pImageShowLabel);
	m_pImageWidgetScroll->setWidgetResizable(true);

	m_pImageShowLabel->setMinimumSize(m_nShowWidth, m_nShowHeight);

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->StopCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStopCapture()));

	connect(m_pImageShowLabel, SIGNAL(sigmousePressEvent(QMouseEvent*)), this, SLOT(smousePressEvent(QMouseEvent*)));
	connect(m_pImageShowLabel, SIGNAL(sigmouseReleaseEvent(QMouseEvent*)), this, SLOT(smouseReleaseEvent(QMouseEvent*)));
	connect(m_pImageShowLabel, SIGNAL(sigmouseMoveEvent(QMouseEvent*)), this, SLOT(smouseMoveEvent(QMouseEvent*)));
	connect(m_pImageShowLabel, SIGNAL(sigmouseDoubleClickEvent(QMouseEvent*)), this, SLOT(smouseDoubleClickEvent(QMouseEvent*)));
	connect(m_pImageShowLabel, SIGNAL(sigwheelEvent(QWheelEvent*)), this, SLOT(swheelEvent(QWheelEvent*)));


	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);

	int nRet = KSJSCZ_Init();

	nRet = KSJSCZ_SetGain(0, 128);
	nRet = KSJSCZ_SetExposureLines(0, 500);

	//nRet = KSJSCZ_SetVideoWidgetPos(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	//nRet = KSJSCZ_SetPosition(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, 0, 0, 1280, 1024);

	KSJSCZ_SetTriggerMode(0, KSJSCZ_TM_CMD_CONTINUE);

	StartCaptureThread();
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	KillCaptureThread();

	KSJSCZ_UnInit();

	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	if (m_pImage != NULL)
	{
		if (m_nShowWidth != m_pixmapToShow.width() || m_nShowHeight != m_pixmapToShow.height())
		{
			m_pixmapToShow = QPixmap::fromImage(m_pImage->scaled(m_nShowWidth, m_nShowHeight));
		}

		m_pImageShowLabel->setPixmap(m_pixmapToShow);
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

static QVector<QRgb> grayTable;

void CKSJSCZDemoMainWindow::ConvertToQImage(unsigned char* pImageData, int w, int h)
{
	if (m_pImage != NULL && (m_pImage->width() != w || m_pImage->height() != h))
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if (m_pImage == NULL)
	{
		m_pImage = new QImage(w, h, QImage::Format_Indexed8);
		
		if (grayTable.size() <= 0)
		{
			for (int i = 0; i < 256; i++) grayTable.push_back(qRgb(i, i, i));
		}

		m_pImage->setColorTable(grayTable);
	}

	memcpy(m_pImage->bits(), pImageData, w*h);

	update();
}

void CKSJSCZDemoMainWindow::resizeEvent(QResizeEvent * event)
{
	m_pImageWidgetScroll->setGeometry(0, 0, 960, 720);
}

void CKSJSCZDemoMainWindow::smousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_ptLastMouse = e->pos();
	}
}

void CKSJSCZDemoMainWindow::smouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
	}
}

void CKSJSCZDemoMainWindow::smouseMoveEvent(QMouseEvent * e)
{
	if (!(e->buttons()&Qt::RightButton) && (e->buttons() == Qt::LeftButton))
	{
		int nMin = m_pImageWidgetScroll->horizontalScrollBar()->minimum();
		int nMax = m_pImageWidgetScroll->horizontalScrollBar()->maximum();
		int nPos = m_pImageWidgetScroll->horizontalScrollBar()->sliderPosition();
		
		if (nMax > nMin)
		{
			int nNew = nPos + m_ptLastMouse.x() - e->pos().x();


			if (nNew < nMin) nNew = nMin;
			else if (nNew>nMax) nNew = nMax;

			m_pImageWidgetScroll->horizontalScrollBar()->setSliderPosition(nNew);
		}

		nMin = m_pImageWidgetScroll->verticalScrollBar()->minimum();
		nMax = m_pImageWidgetScroll->verticalScrollBar()->maximum();
		nPos = m_pImageWidgetScroll->verticalScrollBar()->sliderPosition();

		if (nMax > nMin)
		{
			int nNew = nPos + m_ptLastMouse.y() - e->pos().y();


			if (nNew < nMin) nNew = nMin;
			else if (nNew>nMax) nNew = nMax;

			m_pImageWidgetScroll->verticalScrollBar()->setSliderPosition(nNew);
		}
	}

	m_ptLastMouse = e->pos();

	if (m_ptLastMouse.y() <= 960)
	{
		ui->InfoLabel->setText("Position: (" + QString::number(m_ptLastMouse.x()) + "," + QString::number(m_ptLastMouse.y()) + ")");
	}
}

void CKSJSCZDemoMainWindow::smouseDoubleClickEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)   //ÓÒ¼üË«»÷
	{
		m_nShowWidth = 960-10;
		m_nShowHeight = 720-10;
		m_pImageShowLabel->setMinimumSize(m_nShowWidth, m_nShowHeight);
		update();
		printf("m_nShowWidth:%d - m_nShowHeight:%d\r\n", m_nShowWidth, m_nShowHeight);
	}
}

void CKSJSCZDemoMainWindow::swheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0)
	{
		if (m_nShowWidth < 4800 && m_nShowHeight < 3600)
		{
			m_nShowWidth *= 1.1;
			m_nShowHeight *= 1.1;
			m_pImageShowLabel->setMinimumSize(m_nShowWidth, m_nShowHeight);

			if (m_nShowWidth < 960)
			{
				m_pImageShowLabel->setGeometry((960 - m_nShowWidth) / 2, (720 - m_nShowHeight) / 2, m_nShowWidth, m_nShowHeight);
			}

			update();
			printf("m_nShowWidth:%d - m_nShowHeight:%d\r\n", m_nShowWidth, m_nShowHeight);
		}
	}
	else
	{
		if (m_nShowWidth > 96 && m_nShowHeight > 72)
		{
			m_nShowWidth /= 1.1;
			m_nShowHeight /= 1.1;
			m_pImageShowLabel->setMinimumSize(m_nShowWidth, m_nShowHeight);

			if (m_nShowWidth < 960)
			{
				m_pImageShowLabel->setGeometry((960 - m_nShowWidth) / 2, (720 - m_nShowHeight) / 2, m_nShowWidth, m_nShowHeight);
			}

			update();
			printf("m_nShowWidth:%d - m_nShowHeight:%d\r\n", m_nShowWidth, m_nShowHeight);
		}
	}
}
