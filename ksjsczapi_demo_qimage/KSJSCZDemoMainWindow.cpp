

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
, m_nImageLastWidth(0)
, m_nImageLastHeight(0)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);

	m_pImageZoomer = new CKSJVBImageZoom();

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->StopCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStopCapture()));
	connect(ui->HorizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(OnHorScrollbar(int)));
	connect(ui->VerticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(OnVerScrollbar(int)));

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);

	m_rcClient.setRect(0, 0, DEFAULT_WND_WIDTH - 16, DEFAULT_WND_HEIGHT - 16);
	m_pImageZoomer->SetClientSize(DEFAULT_WND_WIDTH - 16, DEFAULT_WND_HEIGHT - 16);

	ui->VerticalScrollBar->setGeometry(DEFAULT_WND_WIDTH - 16, 0, 16, DEFAULT_WND_HEIGHT - 16);
	ui->HorizontalScrollBar->setGeometry(0, DEFAULT_WND_HEIGHT - 16, DEFAULT_WND_WIDTH - 16, 16);
	ui->VerticalScrollBar->setRange(0, 0);
	ui->HorizontalScrollBar->setRange(0, 0);
	//ui->VerticalScrollBar->setVisible(false);
	//ui->HorizontalScrollBar->setVisible(false);

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

	delete m_pImageZoomer;
	m_pImageZoomer = NULL;

	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	if (m_pImage != NULL)
	{
		if (m_nImageLastWidth != m_pImage->width() || m_nImageLastHeight != m_pImage->height())
		{
			m_pImageZoomer->SetImageSize(m_pImage->width(), m_pImage->height());

			m_nImageLastWidth = m_pImage->width();
			m_nImageLastHeight = m_pImage->height();
		}

		QPainter painter(this);

		int sx, sy, sw, sh, dx, dy, dw, dh;

		m_pImageZoomer->GetValidShowPosition(sx, sy, sw, sh, dx, dy, dw, dh);

		painter.drawImage(QRect(dx, dy, dw, dh), *m_pImage, QRect(sx, sy, sw, sh));
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
			ResetScrollerInfo();
			update();
		}
	}

	m_ptLastMouse = e->pos();

	if (m_ptLastMouse.y() <= 960)
	{
		ui->InfoLabel->setText("Position: (" + QString::number(m_ptLastMouse.x()) + "," + QString::number(m_ptLastMouse.y()) + ")");
	}
}

void CKSJSCZDemoMainWindow::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)   //�Ҽ�˫��
	{
		m_pImageZoomer->SetZoomMode(ZM_FITIMG);
		ResetScrollerInfo();
		update();
	}
}

void CKSJSCZDemoMainWindow::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0)
	{
		ZoomIn(event->x(), event->y());
		ResetScrollerInfo();
		update();
	}
	else
	{
		ZoomOut(event->x(), event->y());
		ResetScrollerInfo();
		update();
	}
}

void CKSJSCZDemoMainWindow::ResetScrollerInfo()
{
	if (m_pImageZoomer != NULL)
	{
		int x, y, w, h, dx, dy;

		m_pImageZoomer->GetOffset(dx, dy);
		m_pImageZoomer->GetImageShowPosition(x, y, w, h);

		if (w > m_rcClient.width()) ui->HorizontalScrollBar->setRange(0, w - m_rcClient.width());
		else ui->HorizontalScrollBar->setRange(0, 0);

		ui->HorizontalScrollBar->setValue(-dx);

		if (h > m_rcClient.height()) ui->VerticalScrollBar->setRange(0, h - m_rcClient.height());
		else ui->VerticalScrollBar->setRange(0, 0);

		ui->VerticalScrollBar->setValue(-dy);
	}
	else
	{
		ui->VerticalScrollBar->setRange(0, 0);
		ui->HorizontalScrollBar->setRange(0, 0);
	}
}

void CKSJSCZDemoMainWindow::OnVerScrollbar(int value)
{
	int x, y;
	m_pImageZoomer->GetOffset(x,y);
	m_pImageZoomer->SetOffset(x, -value);

	this->update();
}

void CKSJSCZDemoMainWindow::OnHorScrollbar(int value)
{
	int x, y;
	m_pImageZoomer->GetOffset(x, y);
	m_pImageZoomer->SetOffset(-value, y);

	this->update();
}
