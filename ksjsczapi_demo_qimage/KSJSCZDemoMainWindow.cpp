

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

			// 得到图像的大小信息，和初始化的时候KSJSCZ_SetCaptureFieldOfView函数设置有关
			KSJSCZ_GetCaptureSize(0, &nWidth, &nHeight, &nBitCount);

			unsigned char *pImageData = NULL;

			// 采集图像
			if (KSJSCZ_ERR_SUCCESS == KSJSCZ_CaptureData(0, &pImageData))
			{
				// 采集图像以后，将内存数据转换成QImage数据,这样pImageData的数据就被转移到QImage里面，以后可以自己进行算法操作
				pMainWindow->ConvertToQImage(pImageData, nWidth, nHeight);
				// 读取图像以后，一定要KSJSCZ_ReleaseBuffer，这样FPGA就把这个内存清空，可以重新将图像采集到这个内存区
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

	// 建立信号和槽的关联
	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->StopCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStopCapture()));
	connect(ui->HorizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(OnHorScrollbar(int)));
	connect(ui->VerticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(OnVerScrollbar(int)));

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);

	// 设置图像显示的区域
	m_rcClient.setRect(0, 0, DEFAULT_WND_WIDTH - 16, DEFAULT_WND_HEIGHT - 16);
	// 告诉Zoomer计算器，图像显示区域的大小
	m_pImageZoomer->SetClientSize(DEFAULT_WND_WIDTH - 16, DEFAULT_WND_HEIGHT - 16);
	// 设置滚动条的位置
	ui->VerticalScrollBar->setGeometry(DEFAULT_WND_WIDTH - 16, 0, 16, DEFAULT_WND_HEIGHT - 16);
	ui->HorizontalScrollBar->setGeometry(0, DEFAULT_WND_HEIGHT - 16, DEFAULT_WND_WIDTH - 16, 16);

	ui->VerticalScrollBar->setRange(0, 0);
	ui->HorizontalScrollBar->setRange(0, 0);
	//ui->VerticalScrollBar->setVisible(false);
	//ui->HorizontalScrollBar->setVisible(false);

	// 初始化
	int nRet = KSJSCZ_Init();

	// 设置增益和曝光,这个根据实际情况设置
	nRet = KSJSCZ_SetGain(0, 128);
	nRet = KSJSCZ_SetExposureLines(0, 500);

	// 不使用硬件的PL显示方式，这个地方不用设置
	//nRet = KSJSCZ_SetVideoWidgetPos(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	//nRet = KSJSCZ_SetPosition(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	// 设置采集的视场范围，最大就是1280X1024
	nRet = KSJSCZ_SetCaptureFieldOfView(0, 0, 0, 1280, 1024);

	// 设置触发模式
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
	// 图像不为空，则开始显示
	if (m_pImage != NULL)
	{
		// 图像大小改变或者初始状态，需要把图像大小给Zommer
		if (m_nImageLastWidth != m_pImage->width() || m_nImageLastHeight != m_pImage->height())
		{
			m_pImageZoomer->SetImageSize(m_pImage->width(), m_pImage->height());

			m_nImageLastWidth = m_pImage->width();
			m_nImageLastHeight = m_pImage->height();
		}

		QPainter painter(this);

		int sx, sy, sw, sh, dx, dy, dw, dh;

		// 取得图像的显示位置信息，Zoomer会计算出图像的哪些部分(sx, sy, sw, sh)应该显示到显示屏上的哪个位置(dx, dy, dw, dh)
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
	// 开始采集
	m_bIsCapturing = true;

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);
}

void CKSJSCZDemoMainWindow::OnStopCapture()
{
	// 停止采集
	m_bIsCapturing = false;

	ui->StartCapturePushButton->setEnabled(!m_bIsCapturing);
	ui->StopCapturePushButton->setEnabled(m_bIsCapturing);
}

static QVector<QRgb> grayTable;

void CKSJSCZDemoMainWindow::ConvertToQImage(unsigned char* pImageData, int w, int h)
{
	// 如果图像大小有改变，把老的m_pImage删除掉
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
		// Zoomer进行一次ZoomIn操作
		m_pImageZoomer->ZoomIn(nClientX, nClientY);
		// 更新显示，更新显示的时候会从Zoomer得到运算以后的显示数据
		this->update();
	}
}

void CKSJSCZDemoMainWindow::ZoomOut(int nClientX, int nClientY)
{
	if (m_pImageZoomer != NULL)
	{
		// Zoomer进行一次ZoomOut操作
		m_pImageZoomer->ZoomOut(nClientX, nClientY);
		// 更新显示，更新显示的时候会从Zoomer得到运算以后的显示数据
		this->update();
	}
}

void CKSJSCZDemoMainWindow::SetZoomMode(KSJ_ZOOM_MODE mode)
{
	if (m_pImageZoomer != NULL)
	{
		// Zoomer进行模式改变
		m_pImageZoomer->SetZoomMode(mode);
		// 更新显示，更新显示的时候会从Zoomer得到运算以后的显示数据
		this->update();
	}
}

void CKSJSCZDemoMainWindow::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
		// 左键按下，记录位置
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
	// 鼠标左键移动
	if (!(e->buttons()&Qt::RightButton) && (e->buttons() == Qt::LeftButton))
	{
		if (m_pImageZoomer != NULL)
		{
			// 告诉Zoomer进行移动运算
			m_pImageZoomer->Move(e->pos().x() - m_ptLastMouse.x(), e->pos().y() - m_ptLastMouse.y());
			// 更新滚动条
			ResetScrollerInfo();
			// 更新显示，更新显示的时候会从Zoomer得到运算以后的显示数据
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
	// 右键双击，把模式改为自适应
	if (e->button() == Qt::RightButton)   //右键双击
	{
		// 模式改为自适应
		m_pImageZoomer->SetZoomMode(ZM_FITIMG);
		// 更新滚动条
		ResetScrollerInfo();
		// 更新显示，更新显示的时候会从Zoomer得到运算以后的显示数据
		update();
	}
}

void CKSJSCZDemoMainWindow::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0)
	{
		// 向上滚动进行一次ZoomIn操作
		ZoomIn(event->x(), event->y());
		ResetScrollerInfo();
		update();
	}
	else
	{
		// 向下滚动进行一次ZoomOut操作
		ZoomOut(event->x(), event->y());
		ResetScrollerInfo();
		update();
	}
}

void CKSJSCZDemoMainWindow::ResetScrollerInfo()
{
	// 设置滚动条
	if (m_pImageZoomer != NULL)
	{
		int x, y, w, h, dx, dy;

		// 得到当前图像移动的零点位置
		m_pImageZoomer->GetOffset(dx, dy);
		// 得到缩放以后图像的位置信息 
		m_pImageZoomer->GetImageShowPosition(x, y, w, h);

		// 设置滚动条，滚动条的范围就是0到，图像大小减去显示区域的大小
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
	// 垂直滚动条移动，所以只改变y方向的，滚动条的值就是图像的位移量value
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
