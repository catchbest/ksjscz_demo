

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


CKSJSCZDemoMainWindow::CKSJSCZDemoMainWindow(QWidget *parent) :
QDialog(parent)
, ui(new Ui::KSJSCZDemoMainWindow)
, m_pImage(NULL)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));

	int nRet = KSJSCZ_Init();
  adfkjasdfk;
	nRet = KSJSCZ_SetGain(0, 128);
	nRet = KSJSCZ_SetExposureLines(0, 500);

	nRet = KSJSCZ_SetVideoWidgetPos(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetPosition(0, 0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, 0, 0, 1280, 1024);

	KSJSCZ_SetTriggerMode(0, KSJSCZ_TM_CMD_CONTINUE);
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	KSJSCZ_UnInit();


    if(m_pImage!=NULL)
    {
        delete m_pImage;
        m_pImage = NULL;
    }

	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

    if(m_pImage!=NULL)
    {
        painter.drawImage(QRect(0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT), *m_pImage);
    }
    //painter.drawRect(QRect(0, 0, DEFAULT_WND_WIDTH, DEFAULT_WND_HEIGHT));
}

void CKSJSCZDemoMainWindow::OnStartCapture()
{
    int nWidth, nHeight, nBitCount;

    if (KSJSCZ_GetCaptureSize(0, &nWidth, &nHeight, &nBitCount) != KSJSCZ_ERR_SUCCESS)return;

    printf("KSJSCZ_GetCaptureSize: %d - %d - %d\r\n", nWidth, nHeight, nBitCount);

    if (m_pImage!=NULL)
    {
         if((m_pImage->width()!=nWidth) || (m_pImage->height()!=nHeight))
         {
             delete m_pImage;
             m_pImage = NULL;
         }
    }

    if (m_pImage==NULL)
    {
        m_pImage = new QImage(nWidth, nHeight, QImage::Format_Indexed8);

        QVector<QRgb> grayTable;

        for (int i = 0; i < 256; i++) grayTable.push_back(qRgb(i, i, i));

        m_pImage->setColorTable(grayTable);
    }

    unsigned char *pImageData = NULL;

    if (KSJSCZ_ERR_SUCCESS == KSJSCZ_CaptureData(0, &pImageData))
    {
        memcpy(m_pImage->bits(), pImageData, nWidth*nHeight);

        KSJSCZ_ReleaseBuffer(0);

        this->update();
    }
}
