

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtCore/QSettings>

#include "KSJSCZDemoMainWindow.h"

#ifdef WIN32
#include "GeneratedFiles/ui_KSJSCZDemoMainWindow.h"
#else
#include <unistd.h>
#include <sys/time.h>
#include "ui_KSJSCZDemoMainWindow.h"
#endif

#include "../ksjsczapi_include/KSJSczApiShow.h"
#include "../ksjsczapi_include/KSJSCZApiBase.h"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"
#include "../ksjsczapi_include/KSJSCZApiIo.h"
#include "../ksjsczapi_include/KSJSczApiCode.h"
#include "../ksjsczapi_include/KSJSczApiInternal.h"
#include "../ksjsczapi_include/KSJSczCom.h"

#include "../zbar.inc/zbar.h"



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


using namespace zbar;


#define  DEFAULT_WND_WIDTH   960
#define  DEFAULT_WND_HEIGHT  720


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

			int nRet = KSJSCZ_CaptureData(0, &pImageData);

			if (KSJSCZ_ERR_SUCCESS == nRet)
			{
				pMainWindow->m_nCaptureCount++;

				if (pMainWindow->m_bParseZbarDemo)
				{
					pMainWindow->ParseZbar(pImageData, nWidth, nHeight);
				}

				//char szPath[64] = { 0 };
				//sprintf(szPath, "/picture/data/Pic%02d.bmp", pMainWindow->m_nCaptureCount % 50);
				//KSJSCZ_HelperSaveToBmp(pImageData, nWidth, nHeight, 8, szPath);

				KSJSCZ_ShowCaptureData(0, pImageData);

				KSJSCZ_ReleaseBuffer(0);
			}

			pMainWindow->SingleCaptureCompleted();
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
, m_nCaptureCountPre(0)
, m_nCaptureCount(0)
, m_nParseZbarCount(0)
, m_nParseZbarFailedCount(0)
, m_bStopCaptureThread(false)
, m_bIsCapturing(false)
, m_bParseZbarDemo(true)
, m_bIsMirror(false)
, m_bIsFlip(false)
, m_nCaptureInterruptThreadId(-1)
, m_bDcodeEAN13(true)
, m_bDcodeEAN8(true)
, m_bDcodeUPCA(true)
, m_bDcodeUPCE(true)
, m_bDcodeISBN10(true)
, m_bDcodeISBN13(true)
, m_bDcodeI25(true)
, m_bDcodeCODE39(true)
, m_bDcodeCODE128(true)
, m_bDcodePDF417(true)
, m_bDcodeQRCODE(true)
, m_nDensity(1)
, m_nTriggerMode(KSJSCZ_TM_CMD_SINGLE)
, m_bALedShine(false)
, m_bBLedShine(false)
, m_ucLedShineValue(0)
, m_nTimeTick(0)
, m_nExpLines(2)
, m_nGain(128)
, m_nDelay(0)
, m_nLastShowTick(-1)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	m_pTimerFrameRate = new QTimer(this);
	//setStyleSheet("background-color: black");

	connect(ui->TriggerModeComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTriggerModeChanged(int)));
	connect(ui->ExpLinesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnExpLinesChanged(int)));
	connect(ui->GainSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnGainChanged(int)));
	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));
	connect(ui->SetFovPushButton, SIGNAL(clicked()), this, SLOT(OnSetFov()));
	connect(ui->TriggerDelaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnTriggerDelayChanged(int)));
	connect(ui->ProcessDataCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnProcessDataChkBoxStateChanged(int)));
	connect(ui->MirrorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnMirrorChkBoxStateChanged(int)));
	connect(ui->FlipCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnFlipChkBoxStateChanged(int)));

	connect(ui->ParseEAN13CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnEan13ChkBoxStateChanged(int)));
	connect(ui->ParseEAN8CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnEan8ChkBoxStateChanged(int)));
	connect(ui->ParseUPCACheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnUPCAChkBoxStateChanged(int)));
	connect(ui->ParseUPCECheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnUPCEChkBoxStateChanged(int)));
	connect(ui->ParseISBN10CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnISBN10ChkBoxStateChanged(int)));
	connect(ui->ParseISBN13CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnISBN13ChkBoxStateChanged(int)));
	connect(ui->ParseI25CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnI25ChkBoxStateChanged(int)));
	connect(ui->ParseCODE39CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnCODE39ChkBoxStateChanged(int)));
	connect(ui->ParseCODE128CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnCODE128ChkBoxStateChanged(int)));
	connect(ui->ParsePDF417CheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnPDF417ChkBoxStateChanged(int)));
	connect(ui->ParseQRCODECheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnQRCODEChkBoxStateChanged(int)));
	connect(m_pTimerFrameRate, SIGNAL(timeout()), this, SLOT(OnTimerFrameRate()));

	connect(ui->DensitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnDensitySpinBoxChanged(int)));

	LoadUserParams();

	ui->StartCapturePushButton->setText(m_bIsCapturing ? "Stop" : "Start");
	ui->ProcessDataCheckBox->setCheckState(m_bParseZbarDemo ? Qt::Checked : Qt::Unchecked);

	ui->TriggerModeComBox->blockSignals(true);
	ui->TriggerModeComBox->addItem("Software Command Continue");
	ui->TriggerModeComBox->addItem("Software Single Trigger");
	ui->TriggerModeComBox->addItem("External Trigger (High Level)");
	ui->TriggerModeComBox->addItem("External Trigger (Low Level)");
	ui->TriggerModeComBox->addItem("External Trigger (Positive Edge)");
	ui->TriggerModeComBox->addItem("External Trigger (Negative Edge)");
	ui->TriggerModeComBox->setCurrentIndex(m_nTriggerMode);
	ui->TriggerModeComBox->blockSignals(false);

	if (m_nCaptureColSize <= 0 || m_nCaptureColSize > 1280 || m_nCaptureRowSize <= 0 || m_nCaptureRowSize > 1024)
	{
		m_nCaptureColStart = (1280 - 640) / 2;
		m_nCaptureColSize = 640;
		m_nCaptureRowStart = (1024 - 480) / 2;
		m_nCaptureRowSize = 480;
	}

	ui->ColStartSpinBox->blockSignals(true);
	ui->ColSizeSpinBox->blockSignals(true);
	ui->RowStartSpinBox->blockSignals(true);
	ui->RowSizeSpinBox->blockSignals(true);
	ui->ColStartSpinBox->setRange(0, ((1280 - m_nCaptureColSize) < (1280 - 8)) ? (1280 - m_nCaptureColSize) : (1280 - 8));
	ui->ColSizeSpinBox->setRange(8, 1280 - m_nCaptureColStart);
	ui->RowStartSpinBox->setRange(0, ((1024 - m_nCaptureRowSize) < (1024 - 8)) ? (1024 - m_nCaptureRowSize) : (1024 - 8));
	ui->RowSizeSpinBox->setRange(8, 1024 - m_nCaptureRowStart);

	ui->ColStartSpinBox->setValue(m_nCaptureColStart);
	ui->ColSizeSpinBox->setValue(m_nCaptureColSize);
	ui->RowStartSpinBox->setValue(m_nCaptureRowStart);
	ui->RowSizeSpinBox->setValue(m_nCaptureRowSize);
	ui->ColStartSpinBox->blockSignals(false);
	ui->ColSizeSpinBox->blockSignals(false);
	ui->RowStartSpinBox->blockSignals(false);
	ui->RowSizeSpinBox->blockSignals(false);

	ui->StartCapturePushButton->setText(m_bIsCapturing ? "Stop" : "Start");

	KSJCOM_Init();

	int nRet = KSJSCZ_ERR_SUCCESS;

	nRet = KSJSCZ_LogSet(1, NULL);
	nRet = KSJSCZ_Init();

	unsigned long ulRegValue;

	KSJSCZ_RdRegFPGA(0, 0x00, &ulRegValue);

	int nMaj1, nMaj2, nMin1, nMin2;
	nRet = KSJSCZ_GetLibVersion(&nMaj1, &nMaj2, &nMin1, &nMin2);
	ui->StaticText_Version->setText(QString("V1.1 (Lib: %1.%2.%3.%4 FPGA: %5.%6)").arg(nMaj1).arg(nMaj2).arg(nMin1).arg(nMin2).arg(ulRegValue >> 8 & 0x00FF).arg(ulRegValue & 0x00FF));

	nRet = KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);

	printf("KSJSCZ_SetCaptureFieldOfView: %d - %d - %d - %d\r\n", m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);

	ResetShowPositions();
	UpdateUiSetting();

	nRet = KSJSCZ_SetTriggerMode(0, m_nTriggerMode);

	printf("KSJSCZ_SetTriggerMode %d\r\n", m_nTriggerMode);

	KSJSCZ_WrRegFPGA(0, 0x9C, 0);

	if (KSJCOM_Open(1, 115200, 8, 1) != KSJCOM_RET_SUCCESS)
	{
		printf("=== open the com port failed! === \r\n");
	}

	char *data = "Com is conneted!\r\n";

	if (KSJCOM_SendData(1, (unsigned char*)data, 18) != KSJCOM_RET_SUCCESS)
	{
		printf("=== Com write wrong! === \r\n");
	}
	else
	{
		printf("=== Com is conneted! === \r\n");
	}

	StartCaptureThread();

	m_nTimeTick = 0;
	m_pTimerFrameRate->setInterval(200);
	m_pTimerFrameRate->start();
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	if (m_pTimerFrameRate->isActive()) m_pTimerFrameRate->stop();

	KillCaptureThread();

	KSJSCZ_UnInit();
	KSJCOM_UnInit();

	delete ui;
}


void CKSJSCZDemoMainWindow::changeEvent(QEvent *event)
{
}

void CKSJSCZDemoMainWindow::mouseMoveEvent(QMouseEvent *e)
{

}

void CKSJSCZDemoMainWindow::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)   //左键双击
	{
		m_nImagePositionLeft = -480;
		m_nImagePositionTop = -360;
		m_nImagePositionWidth = 1920;
		m_nImagePositionHeight = 1440;

		KSJSCZ_SetPosition(0, m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);

		printf("KSJSCZ_SetPosition(0, %d, %d, %d, %d)\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
	}
	else
	{
		if (m_nImagePositionLeft != 0 || m_nImagePositionTop != 0 || m_nImagePositionWidth != m_nVideoWidgetWidth || m_nImagePositionHeight != m_nVideoWidgetHeight)
		{
			m_nImagePositionLeft = 0;
			m_nImagePositionTop = 0;
			m_nImagePositionWidth = m_nVideoWidgetWidth;
			m_nImagePositionHeight = m_nVideoWidgetHeight;

			KSJSCZ_SetPosition(0, m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);

			printf("KSJSCZ_SetPosition(0, %d, %d, %d, %d)\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
		}
	}
}

void CKSJSCZDemoMainWindow::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0)
	{
		if (m_nImagePositionWidth > 320)
		{

			printf("--> KSJSCZ_SetPosition(0, %d, %d, %d, %d)\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
			m_nImagePositionLeft += 4;
			m_nImagePositionTop += 3;
			m_nImagePositionWidth -= 8;
			m_nImagePositionHeight -= 6;

			KSJSCZ_SetPosition(0, m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);

			printf("<-- KSJSCZ_SetPosition(0, %d, %d, %d, %d)\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
		}
	}
	else
	{
		if (m_nImagePositionWidth < 2560)
		{
			printf("--> KSJSCZ_SetPosition(0, %d, %d, %d, %d)\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);

			m_nImagePositionLeft -= 4;
			m_nImagePositionTop -= 3;
			m_nImagePositionWidth += 8;
			m_nImagePositionHeight += 6;

			KSJSCZ_SetPosition(0, m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);

			printf("<-- KSJSCZ_SetPosition(0, %d, %d, %d, %d)\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
		}
	}
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.setPen(Qt::NoPen);

	painter.setBrush(Qt::black);
	painter.drawRect(QRect(m_nVideoWidgetLeft, m_nVideoWidgetTop, m_nVideoWidgetWidth, m_nVideoWidgetHeight));
}

void CKSJSCZDemoMainWindow::mousePressEvent(QMouseEvent *e)
{

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

void CKSJSCZDemoMainWindow::UpdateUiSetting()
{
	float fValue, fValueMin, fValueMax;
	unsigned long ulValue, ulValueMin, ulValueMax;

	KSJSCZ_SetExposureLines(0, m_nExpLines);
	KSJSCZ_GetExposureLinesRange(0, &ulValueMin, &ulValueMax);
	ui->ExpLinesSpinBox->setRange(ulValueMin > 2 ? ulValueMin : 2, ulValueMax);
	ui->ExpLinesSpinBox->setValue(m_nExpLines);

	KSJSCZ_SetGain(0, m_nGain);
	KSJSCZ_GetGainRange(0, &ulValueMin, &ulValueMax);
	ui->GainSpinBox->setRange(ulValueMin, ulValueMax);
	ui->GainSpinBox->setValue(m_nGain);

	KSJSCZ_SetTriggerDelay(0, m_nDelay);
	KSJSCZ_GetTriggerDelayRange(0, &ulValueMin, &ulValueMax);
	ui->TriggerDelaySpinBox->setRange(ulValueMin, ulValueMax);
	ui->TriggerDelaySpinBox->setValue(m_nDelay);

	ui->ColStartSpinBox->setRange(0, 1280);
	ui->ColSizeSpinBox->setRange(0, 1280);
	ui->RowStartSpinBox->setRange(0, 1024);
	ui->RowSizeSpinBox->setRange(0, 1024);

	ui->ColStartSpinBox->setValue(m_nCaptureColStart);
	ui->ColSizeSpinBox->setValue(m_nCaptureColSize);
	ui->RowStartSpinBox->setValue(m_nCaptureRowStart);
	ui->RowSizeSpinBox->setValue(m_nCaptureRowSize);

	ui->ParseEAN13CheckBox->setCheckState(m_bDcodeEAN13 ? Qt::Checked : Qt::Unchecked);
	ui->ParseEAN8CheckBox->setCheckState(m_bDcodeEAN8 ? Qt::Checked : Qt::Unchecked);
	ui->ParseUPCACheckBox->setCheckState(m_bDcodeUPCA ? Qt::Checked : Qt::Unchecked);
	ui->ParseUPCECheckBox->setCheckState(m_bDcodeUPCE ? Qt::Checked : Qt::Unchecked);
	ui->ParseISBN10CheckBox->setCheckState(m_bDcodeISBN10 ? Qt::Checked : Qt::Unchecked);
	ui->ParseISBN13CheckBox->setCheckState(m_bDcodeISBN13 ? Qt::Checked : Qt::Unchecked);
	ui->ParseI25CheckBox->setCheckState(m_bDcodeI25 ? Qt::Checked : Qt::Unchecked);
	ui->ParseCODE39CheckBox->setCheckState(m_bDcodeCODE39 ? Qt::Checked : Qt::Unchecked);
	ui->ParseCODE128CheckBox->setCheckState(m_bDcodeCODE128 ? Qt::Checked : Qt::Unchecked);
	ui->ParsePDF417CheckBox->setCheckState(m_bDcodePDF417 ? Qt::Checked : Qt::Unchecked);
	ui->ParseQRCODECheckBox->setCheckState(m_bDcodeQRCODE ? Qt::Checked : Qt::Unchecked);

	ui->DensitySpinBox->setValue(m_nDensity);

	KSJSCZ_SetMirror(0, m_bIsMirror);
	ui->MirrorCheckBox->setCheckState(m_bIsMirror ? Qt::Checked : Qt::Unchecked);

	KSJSCZ_SetMirror(0, m_bIsFlip);
	ui->FlipCheckBox->setCheckState(m_bIsFlip ? Qt::Checked : Qt::Unchecked);
}

void CKSJSCZDemoMainWindow::OnTriggerModeChanged(int value)
{
	m_nCaptureCount = 0;
	m_nCaptureCountPre = 0;
	m_nParseZbarCount = 0;
	m_nParseZbarFailedCount = 0;

	m_nTriggerMode = (KSJSCZ_TRIGGER_MODE)value;

	KSJSCZ_SetTriggerMode(0, m_nTriggerMode);
	printf("KSJSCZ_SetTriggerMode %d\r\n", m_nTriggerMode);
	//KSJSCZ_EmptyFrameBuffer(0);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnTriggerDelayChanged(int value)
{
	KSJSCZ_SetTriggerDelay(0, value);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnProcessDataChkBoxStateChanged(int value)
{
	m_bParseZbarDemo = (value == Qt::Checked);
}

void CKSJSCZDemoMainWindow::OnExpLinesChanged(int value)
{
	m_nExpLines = value;
	float fValue;
	KSJSCZ_SetExposureLines(0, m_nExpLines);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnGainChanged(int value)
{
	m_nGain = value;
	KSJSCZ_SetGain(0, m_nGain);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnSetFov()
{
	m_nCaptureColStart = ui->ColStartSpinBox->value();
	m_nCaptureColSize = ui->ColSizeSpinBox->value();
	m_nCaptureRowStart = ui->RowStartSpinBox->value();
	m_nCaptureRowSize = ui->RowSizeSpinBox->value();

	if (m_nCaptureColSize < 8)         m_nCaptureColSize = 8;
	else if (m_nCaptureColSize > 1280) m_nCaptureColSize = 1280;

	if (m_nCaptureRowSize < 8)         m_nCaptureRowSize = 8;
	else if (m_nCaptureRowSize > 1024) m_nCaptureRowSize = 1024;

	if (m_nCaptureColStart < 0)         m_nCaptureColStart = 0;
	else if (m_nCaptureColStart > 1280) m_nCaptureColStart = 1280;

	if (m_nCaptureRowStart < 0)         m_nCaptureRowStart = 0;
	else if (m_nCaptureRowStart > 1280) m_nCaptureRowStart = 1280;

	if ((m_nCaptureColSize + m_nCaptureColStart) > 1280) m_nCaptureColStart = (1280 - m_nCaptureColSize) / 2;
	if ((m_nCaptureRowSize + m_nCaptureRowStart) > 1024) m_nCaptureRowStart = (1024 - m_nCaptureRowSize) / 2;

	ui->ColStartSpinBox->setValue(m_nCaptureColStart);
	ui->ColSizeSpinBox->setValue(m_nCaptureColSize);
	ui->RowStartSpinBox->setValue(m_nCaptureRowStart);
	ui->RowSizeSpinBox->setValue(m_nCaptureRowSize);

	KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);

	printf("KSJSCZ_SetCaptureFieldOfView: %d - %d - %d - %d\r\n", m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);

	ResetShowPositions();

	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnStartCapture()
{
	if ((!m_bIsCapturing) && (m_nTriggerMode != KSJSCZ_TM_CMD_SINGLE))
	{
		m_nCaptureCount = 0;
		m_nCaptureCountPre = 0;
		m_nParseZbarCount = 0;
		m_nParseZbarFailedCount = 0;
	}

	m_bIsCapturing = !m_bIsCapturing;

	ui->StartCapturePushButton->setText(m_bIsCapturing ? "Stop" : "Start");
}

void CKSJSCZDemoMainWindow::OnEan13ChkBoxStateChanged(int value)
{
	m_bDcodeEAN13 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnEan8ChkBoxStateChanged(int value)
{
	m_bDcodeEAN8 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnUPCAChkBoxStateChanged(int value)
{
	m_bDcodeUPCA = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnUPCEChkBoxStateChanged(int value)
{
	m_bDcodeUPCE = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnISBN10ChkBoxStateChanged(int value)
{
	m_bDcodeISBN10 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnISBN13ChkBoxStateChanged(int value)
{
	m_bDcodeISBN13 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnI25ChkBoxStateChanged(int value)
{
	m_bDcodeI25 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnCODE39ChkBoxStateChanged(int value)
{
	m_bDcodeCODE39 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnCODE128ChkBoxStateChanged(int value)
{
	m_bDcodeCODE128 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnPDF417ChkBoxStateChanged(int value)
{
	m_bDcodePDF417 = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnQRCODEChkBoxStateChanged(int value)
{
	m_bDcodeQRCODE = (value == Qt::Checked);
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnDensitySpinBoxChanged(int value)
{
	m_nDensity = value;
	SaveUserParams();
}

void CKSJSCZDemoMainWindow::OnMirrorChkBoxStateChanged(int value)
{
	m_bIsMirror = (value == Qt::Checked);
	SaveUserParams();

	KSJSCZ_SetMirror(0, m_bIsMirror);
}

void CKSJSCZDemoMainWindow::OnFlipChkBoxStateChanged(int value)
{
	m_bIsFlip = (value == Qt::Checked);
	SaveUserParams();

	KSJSCZ_SetFlip(0, m_bIsFlip);
}

void CKSJSCZDemoMainWindow::ParseZbar(unsigned char *pData, int nWidth, int nHeight)
{
	zbar_image_t *pImage = zbar_image_create();
	zbar_image_set_userdata(pImage, NULL);
	zbar_image_set_size(pImage, nWidth, nHeight);
	unsigned long fourcc = (('Y' & 0xff) | (('8' & 0xff) << 8) | (('0' & 0xff) << 16) | (('0' & 0xff) << 24));
	zbar_image_set_format(pImage, fourcc);

	zbar_image_set_data(pImage, pData, nWidth * nHeight, NULL);

	zbar_image_scanner_t *pImageScanner = zbar_image_scanner_create();

	if (m_nDensity <= 0) m_nDensity = 1;

	zbar_image_scanner_set_config(pImageScanner, ZBAR_NONE, ZBAR_CFG_X_DENSITY, m_nDensity);
	zbar_image_scanner_set_config(pImageScanner, ZBAR_NONE, ZBAR_CFG_Y_DENSITY, m_nDensity);

	zbar_image_scanner_set_config(pImageScanner, ZBAR_NONE, ZBAR_CFG_ENABLE, 0);

	if (m_bDcodeEAN13)   zbar_image_scanner_set_config(pImageScanner, ZBAR_EAN13, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeEAN8)    zbar_image_scanner_set_config(pImageScanner, ZBAR_EAN8, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeUPCA)    zbar_image_scanner_set_config(pImageScanner, ZBAR_UPCA, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeUPCE)    zbar_image_scanner_set_config(pImageScanner, ZBAR_UPCE, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeISBN10)  zbar_image_scanner_set_config(pImageScanner, ZBAR_ISBN10, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeISBN13)  zbar_image_scanner_set_config(pImageScanner, ZBAR_ISBN13, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeI25)     zbar_image_scanner_set_config(pImageScanner, ZBAR_I25, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeCODE39)  zbar_image_scanner_set_config(pImageScanner, ZBAR_CODE39, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeCODE128) zbar_image_scanner_set_config(pImageScanner, ZBAR_CODE128, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodePDF417)  zbar_image_scanner_set_config(pImageScanner, ZBAR_PDF417, ZBAR_CFG_ENABLE, 1);
	if (m_bDcodeQRCODE)  zbar_image_scanner_set_config(pImageScanner, ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

	zbar_scan_image(pImageScanner, pImage);

	const zbar_symbol_set_t *pSymbolSet   = zbar_image_get_symbols(pImage);
	const zbar_symbol_t     *pSymbolFirst = zbar_symbol_set_first_symbol(pSymbolSet);

	zbar_symbol_type_t      SymbolType;
	const zbar_symbol_t     *pSymbolCur   = pSymbolFirst;

	QString strZbar = "";

	if (pSymbolCur == NULL)
	{
		KSJCOM_SendData(1, (unsigned char*)"{NG}\r\n", 6);
	}
	else
	{
		while (pSymbolCur)
		{
			SymbolType = zbar_symbol_get_type(pSymbolCur);
			std::string strTypeName = zbar_get_symbol_name(SymbolType);
			std::string strData(zbar_symbol_get_data(pSymbolCur), zbar_symbol_get_data_length(pSymbolCur));;

			strZbar = QString::fromLocal8Bit(strData.c_str());

			KSJCOM_SendData(1, (unsigned char*)"{OK[", 4);
			KSJCOM_SendData(1, (unsigned char*)strData.c_str(), strData.length());
			KSJCOM_SendData(1, (unsigned char*)"]}\r\n", 4);

			if (strZbar != "") break;

			pSymbolCur = zbar_symbol_next(pSymbolCur);
		}
	}

	zbar_image_scanner_destroy(pImageScanner);
	zbar_image_free_data(pImage);

	if (strZbar != "")
	{
		++m_nParseZbarCount;

		strZbar = QString::number(m_nParseZbarCount) + "-[F:" + QString::number(m_nParseZbarFailedCount) + "]: " + strZbar;
	}
	else
	{
		++m_nParseZbarFailedCount;
	}

	ui->StaticText_Zbar->setText(strZbar);
}

void CKSJSCZDemoMainWindow::OnTimerFrameRate()
{
	++m_nTimeTick;

	if (m_nTimeTick >= 5)
	{
		m_nTimeTick = 0;

		char szfps[64] = { 0 };

		sprintf(szfps, "%d FPS", m_nCaptureCount - m_nCaptureCountPre);

		ui->StaticText_FPS->setText(szfps);

		m_nCaptureCountPre = m_nCaptureCount;
	}

	if (m_nTimeTick % 10 == 0)
	{
		m_ucLedShineValue += 1;
		if (m_ucLedShineValue >= 4) m_ucLedShineValue = 0;

		// 这两个灯的红绿顺序相反
		if (m_bALedShine)
		{
			KSJSCZ_GpioSet(6, m_ucLedShineValue & 0x2);
			KSJSCZ_GpioSet(7, m_ucLedShineValue & 0x1);
		}
		if (m_bBLedShine)
		{
			KSJSCZ_GpioSet(9, m_ucLedShineValue & 0x2);
			KSJSCZ_GpioSet(8, m_ucLedShineValue & 0x1);
		}
	}
}

void CKSJSCZDemoMainWindow::SingleCaptureCompleted()
{
	if (m_nTriggerMode == KSJSCZ_TM_CMD_SINGLE)
	{
		m_bIsCapturing = false;

		ui->StartCapturePushButton->setText(m_bIsCapturing ? "Stop" : "Start");
	}
}

void CKSJSCZDemoMainWindow::SaveUserParams()
{
	QSettings setting("/home/user/demo_config.ini", QSettings::IniFormat);

	setting.setValue("m_nExpLines", QString::number(m_nExpLines));
	setting.setValue("m_nGain", QString::number(m_nGain));
	setting.setValue("m_nDelay", QString::number(m_nDelay));

	setting.setValue("m_nCaptureColStart", QString::number(m_nCaptureColStart));
	setting.setValue("m_nCaptureColSize", QString::number(m_nCaptureColSize));
	setting.setValue("m_nCaptureRowStart", QString::number(m_nCaptureRowStart));
	setting.setValue("m_nCaptureRowSize", QString::number(m_nCaptureRowSize));

	setting.setValue("m_bIsMirror", QString::number(m_bIsMirror));
	setting.setValue("m_bIsFlip", QString::number(m_bIsFlip));
	setting.setValue("m_nTriggerMode", QString::number(m_nTriggerMode));

	setting.setValue("m_bDcodeEAN13", QString::number(m_bDcodeEAN13));
	setting.setValue("m_bDcodeEAN8", QString::number(m_bDcodeEAN8));
	setting.setValue("m_bDcodeUPCA", QString::number(m_bDcodeUPCA));
	setting.setValue("m_bDcodeUPCE", QString::number(m_bDcodeUPCE));
	setting.setValue("m_bDcodeISBN10", QString::number(m_bDcodeISBN10));
	setting.setValue("m_bDcodeISBN13", QString::number(m_bDcodeISBN13));
	setting.setValue("m_bDcodeI25", QString::number(m_bDcodeI25));
	setting.setValue("m_bDcodeCODE39", QString::number(m_bDcodeCODE39));
	setting.setValue("m_bDcodeCODE128", QString::number(m_bDcodeCODE128));
	setting.setValue("m_bDcodePDF417", QString::number(m_bDcodePDF417));
	setting.setValue("m_bDcodeQRCODE", QString::number(m_bDcodeQRCODE));

	setting.setValue("m_nDensity", QString::number(m_nDensity));
}

void CKSJSCZDemoMainWindow::LoadUserParams()
{
	QSettings setting("/home/user/demo_config.ini", QSettings::IniFormat);

	m_nExpLines = setting.value("m_nExpLines").toInt();
	m_nGain = setting.value("m_nGain").toInt();
	m_nDelay = setting.value("m_nDelay").toInt();

	if (m_nExpLines < 2) m_nExpLines = 2;
	if (m_nGain <= 0) m_nGain = 128;

	//printf("=======>> %d <<===========\r\n", m_nGain);


	m_nCaptureColStart = setting.value("m_nCaptureColStart").toInt();
	m_nCaptureColSize = setting.value("m_nCaptureColSize").toInt();
	m_nCaptureRowStart = setting.value("m_nCaptureRowStart").toInt();
	m_nCaptureRowSize = setting.value("m_nCaptureRowSize").toInt();

	m_bIsMirror = setting.value("m_bIsMirror").toInt();
	m_bIsFlip = setting.value("m_bIsFlip").toInt();

	m_nTriggerMode = (KSJSCZ_TRIGGER_MODE)setting.value("m_nTriggerMode").toInt();

	m_bDcodeEAN13 = setting.value("m_bDcodeEAN13").toInt();
	m_bDcodeEAN8 = setting.value("m_bDcodeEAN8").toInt();
	m_bDcodeUPCA = setting.value("m_bDcodeUPCA").toInt();
	m_bDcodeUPCE = setting.value("m_bDcodeUPCE").toInt();
	m_bDcodeISBN10 = setting.value("m_bDcodeISBN10").toInt();
	m_bDcodeISBN13 = setting.value("m_bDcodeISBN13").toInt();
	m_bDcodeI25 = setting.value("m_bDcodeI25").toInt();
	m_bDcodeCODE39 = setting.value("m_bDcodeCODE39").toInt();
	m_bDcodeCODE128 = setting.value("m_bDcodeCODE128").toInt();
	m_bDcodePDF417 = setting.value("m_bDcodePDF417").toInt();
	m_bDcodeQRCODE = setting.value("m_bDcodeQRCODE").toInt();

	m_nDensity = setting.value("m_nDensity").toInt();
}

void CKSJSCZDemoMainWindow::ResetShowPositions()
{
	m_nVideoWidgetLeft = 0;
	m_nVideoWidgetTop = 0;
	m_nVideoWidgetWidth = DEFAULT_WND_WIDTH;
	m_nVideoWidgetHeight = DEFAULT_WND_HEIGHT;

	if (m_nCaptureColSize <= 0) m_nCaptureColSize = 640;
	if (m_nCaptureRowSize <= 0) m_nCaptureRowSize = 480;

	float fw = (float)m_nVideoWidgetWidth / m_nCaptureColSize;
	float fh = (float)m_nVideoWidgetHeight / m_nCaptureRowSize;

	printf("VideoWidgetPos: %f - %f - %d - %d\r\n", fw, fh, m_nCaptureColSize, m_nCaptureRowSize);

	if (fw < fh)
	{
		m_nVideoWidgetHeight = ((int)(fw*m_nCaptureRowSize + 0.5)) & 0xfffffffc;
		m_nVideoWidgetTop = (DEFAULT_WND_HEIGHT - m_nVideoWidgetHeight) / 2;
	}
	else
	{
		m_nVideoWidgetWidth = ((int)(fh*m_nCaptureColSize + 0.5)) & 0xfffffffc;
		m_nVideoWidgetLeft = (DEFAULT_WND_WIDTH - m_nVideoWidgetWidth) / 2;
	}

	m_nImagePositionLeft = 0;
	m_nImagePositionTop = 0;
	m_nImagePositionWidth = m_nVideoWidgetWidth;
	m_nImagePositionHeight = m_nVideoWidgetHeight;

	KSJSCZ_SetVideoWidgetPos(0, m_nVideoWidgetLeft, m_nVideoWidgetTop, m_nVideoWidgetWidth, m_nVideoWidgetHeight);
	KSJSCZ_SetPosition(0, m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);

	printf("KSJSCZ_SetVideoWidgetPos: %d - %d - %d - %d\r\n", m_nVideoWidgetLeft, m_nVideoWidgetTop, m_nVideoWidgetWidth, m_nVideoWidgetHeight);
	printf("KSJSCZ_SetPosition: %d - %d - %d - %d\r\n", m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
}