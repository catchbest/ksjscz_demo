
#include <QTimer>
#include <QPainter>
#include <QResizeEvent>


#include "KSJSCZDemoMainWindow.h"

#ifdef WIN32
#include "GeneratedFiles/ui_KSJSCZDemoMainWindow.h"
#else
#include <unistd.h>
#include "LinuxGenFiles/ui_KSJSCZDemoMainWindow.h"
#endif

#include "../ksjsczapi_include/KSJSczApiShow.h"
#include "../ksjsczapi_include/KSJSCZApiBase.h"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"
#include "../ksjsczapi_include/KSJSCZApiIo.h"
#include "../ksjsczapi_include/KSJSczApiCode.h"
#include "../ksjsczapi_include/KSJSczApiInternal.h"

#include "KSJImageThreshold.h"
#include "KSJImageHistgram.h"
#include "KSJImageAoi.h"

void MyProcessData(unsigned char *pData, int nWidth, int nHeight, int nBitCount)
{
	int nHistgramAoiX = nWidth / 4;
	int nHistgramAoiY = nHeight / 4;
	int nHistgramAoiW = nWidth / 2;
	int nHistgramAoiH = nHeight / 2;
	int nHistgram[256];

	KSJIMAGE_Y8_Histgram(pData, nWidth, nHeight, nHistgramAoiX, nHistgramAoiY, nHistgramAoiW, nHistgramAoiH, nHistgram);
	KSJIMAGE_ShowAoi(pData, nWidth, nHeight, nBitCount, nHistgramAoiX, nHistgramAoiY, nHistgramAoiW, nHistgramAoiH);

	int nThresholdAoiX = 0;
	int nThresholdAoiY = 0;
	int nThresholdAoiW = 320;
	int nThresholdAoiH = 240;

	// Threshold = 128, mode = 0 >Threshold = HIGH, <Threshold = LOW
	KSJIMAGE_Y8_ThresholdSingle_AOI(pData, nWidth, nHeight, 128, 0, nThresholdAoiX, nThresholdAoiY, nThresholdAoiW, nThresholdAoiH);
}

void* ThreadForCaptureData(void *arg)
{
	if (NULL == arg)    //传进来CScz指针
	{
		pthread_exit((char*)"ThreadForSignalMode");
	}

	unsigned char ucTick = 0;

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
				MyProcessData(pImageData, nWidth, nHeight, nBitCount);
				KSJSCZ_ShowCaptureData(0, pImageData);
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
, m_bStopCaptureThread(false)
, m_bIsCapturing(true)
, m_nCaptureInterruptThreadId(-1)
, m_nVideoWidgetLeft(0)
, m_nVideoWidgetTop(0)
, m_nVideoWidgetWidth(800)
, m_nVideoWidgetHeight(600)
, m_nImagePositionLeft(0)
, m_nImagePositionTop(0)
, m_nImagePositionWidth(800)
, m_nImagePositionHeight(600)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(ui->TriggerModeComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTriggerModeChanged(int)));
	connect(ui->ExpTimeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(OnExpTimerChanged(double)));
	connect(ui->ExpLinesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnExpLinesChanged(int)));
	connect(ui->GainSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnGainChanged(int)));
	connect(ui->ColStartSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnColStartChanged(int)));
	connect(ui->ColSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnColSizeChanged(int)));
	connect(ui->RowStartSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnRowStartChanged(int)));
	connect(ui->RowSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnRowSizeChanged(int)));
	connect(ui->RegAddressSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnRegAddressChanged(int)));
	connect(ui->RegValueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(OnRegValueChanged(int)));
	connect(ui->ReadRegPushButton, SIGNAL(clicked()), this, SLOT(OnReadReg()));
	connect(ui->WriteRegPushButton, SIGNAL(clicked()), this, SLOT(OnWriteReg()));
	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(OnStartCapture()));

	ui->TriggerModeComBox->blockSignals(true);
	ui->TriggerModeComBox->addItem("Sofatware Command Continue");
	ui->TriggerModeComBox->addItem("Sofatware Single Trigger");
	ui->TriggerModeComBox->addItem("External Trigger (High Level)");
	ui->TriggerModeComBox->addItem("External Trigger (Low Level)");
	ui->TriggerModeComBox->addItem("External Trigger (Positive Edge)");
	ui->TriggerModeComBox->addItem("External Trigger (Negative Edge)");
	ui->TriggerModeComBox->setCurrentIndex(1);
	ui->TriggerModeComBox->blockSignals(false);

	m_nCaptureColStart = (1280 - 800) / 2;
	m_nCaptureColSize = 800;
	m_nCaptureRowStart = (1024 - 600) / 2;
	m_nCaptureRowSize = 600;

	ui->ColStartSpinBox->blockSignals(true);
	ui->ColSizeSpinBox->blockSignals(true);
	ui->RowStartSpinBox->blockSignals(true);
	ui->RowSizeSpinBox->blockSignals(true);
	ui->ColStartSpinBox->setRange(0, ((1280 - m_nCaptureColSize)<(1280 - 8)) ? (1280 - m_nCaptureColSize) : (1280 - 8));
	ui->ColSizeSpinBox->setRange(8, 1280 - m_nCaptureColStart);
	ui->RowStartSpinBox->setRange(0, ((1024 - m_nCaptureRowSize)<(1024 - 8)) ? (1024 - m_nCaptureRowSize) : (1024 - 8));
	ui->RowSizeSpinBox->setRange(8, 1024 - m_nCaptureRowStart);

	ui->ColStartSpinBox->setValue(m_nCaptureColStart);
	ui->ColSizeSpinBox->setValue(m_nCaptureColSize);
	ui->RowStartSpinBox->setValue(m_nCaptureRowStart);
	ui->RowSizeSpinBox->setValue(m_nCaptureRowSize);
	ui->ColStartSpinBox->blockSignals(false);
	ui->ColSizeSpinBox->blockSignals(false);
	ui->RowStartSpinBox->blockSignals(false);
	ui->RowSizeSpinBox->blockSignals(false);

	ui->RegAddressSpinBox->setValue(0x70);
	ui->RegValueSpinBox->setValue(0);
	ui->StaticText_RegAddress->setText("0x70");
	
	ui->StartCapturePushButton->setText(m_bIsCapturing?"Stop":"Start");

	int nRet = KSJSCZ_ERR_SUCCESS;
	int nMaj1, nMaj2, nMin1, nMin2;
	nRet = KSJSCZ_GetLibVersion(&nMaj1, &nMaj2, &nMin1, &nMin2);
	ui->StaticText_Version->setText(QString("KSJSCZApi Ver: %1.%2.%3.%4").arg(nMaj1).arg(nMaj2).arg(nMin1).arg(nMin2));

	nRet = KSJSCZ_Init();

	nRet = KSJSCZ_SetVideoWidgetPos(0, m_nVideoWidgetLeft, m_nVideoWidgetTop, m_nVideoWidgetWidth, m_nVideoWidgetHeight);
	nRet = KSJSCZ_SetPosition(0, m_nImagePositionLeft, m_nImagePositionTop, m_nImagePositionWidth, m_nImagePositionHeight);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);

	nRet = KSJSCZ_SetGain(0, 128);
	nRet = KSJSCZ_SetExposureLines(0, 120);
	nRet = KSJSCZ_SetTriggerMode(0, KSJSCZ_TM_CMD_SINGLE);

	UpdateUiWithCameraSetting();

	StartCaptureThread();
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	KillCaptureThread();

	KSJSCZ_UnInit();

	delete ui;
}


void CKSJSCZDemoMainWindow::changeEvent(QEvent *event)
{
}

void CKSJSCZDemoMainWindow::mouseMoveEvent(QMouseEvent *e)
{
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

void CKSJSCZDemoMainWindow::UpdateUiWithCameraSetting()
{
	float fValue, fValueMin, fValueMax;
	unsigned long ulValue, ulValueMin, ulValueMax;

	KSJSCZ_GetExposureLinesRange(0, &ulValueMin, &ulValueMax);
	ui->ExpLinesSpinBox->setRange(ulValueMin, ulValueMax);
	ui->StaticText_ExpostureLinesRange->setText(QString::number(ulValueMin) + "-" + QString::number(ulValueMax));
	KSJSCZ_GetExposureLines(0, &ulValue);
	ui->ExpLinesSpinBox->setValue(ulValue);

	KSJSCZ_GetExposureTimeRange(0, &fValueMin, &fValueMax);
	ui->ExpTimeSpinBox->setRange(fValueMin, fValueMax);
	ui->StaticText_ExpostureTimeRange->setText(QString::number(fValueMin) + "-" + QString::number(fValueMax));
	KSJSCZ_GetExposureTime(0, &fValue);
	ui->ExpTimeSpinBox->setValue(fValue);

	KSJSCZ_GetGainRange(0, &ulValueMin, &ulValueMax);
	ui->GainSpinBox->setRange(ulValueMin, ulValueMax);
	ui->StaticText_GainRange->setText(QString::number(ulValueMin) + "-" + QString::number(ulValueMax));
	KSJSCZ_GetGain(0, &ulValue);
	ui->GainSpinBox->setValue(ulValue);

	ui->ColStartSpinBox->setValue(m_nCaptureColStart);
	ui->ColSizeSpinBox->setValue(m_nCaptureColSize);
	ui->RowStartSpinBox->setValue(m_nCaptureRowStart);
	ui->RowSizeSpinBox->setValue(m_nCaptureRowSize);
}

void CKSJSCZDemoMainWindow::OnTriggerModeChanged(int value)
{
	KSJSCZ_SetTriggerMode(0, KSJSCZ_TM_CMD_SINGLE);
	KSJSCZ_SetTriggerMode(0, (KSJSCZ_TRIGGER_MODE)value);
}

void CKSJSCZDemoMainWindow::OnExpTimerChanged(double value)
{
	KSJSCZ_SetExposureTime(0, value);
}

void CKSJSCZDemoMainWindow::OnExpLinesChanged(int value)
{
	KSJSCZ_SetExposureLines(0, value);
}

void CKSJSCZDemoMainWindow::OnGainChanged(int value)
{
	m_nCaptureColStart = ui->ColStartSpinBox->value();
	m_nCaptureColSize = ui->ColSizeSpinBox->value();
	m_nCaptureRowStart = ui->RowStartSpinBox->value();
	KSJSCZ_SetGain(0, value);
}

void CKSJSCZDemoMainWindow::OnColStartChanged(int value)
{
	m_nCaptureColStart = ui->ColStartSpinBox->value();
	m_nCaptureColSize = ui->ColSizeSpinBox->value();
	m_nCaptureRowStart = ui->RowStartSpinBox->value();
	m_nCaptureRowSize = ui->RowSizeSpinBox->value();

	ui->ColStartSpinBox->setRange(0, ((1280 - m_nCaptureColSize)<(1280 - 8)) ? (1280 - m_nCaptureColSize) : (1280 - 8));
	ui->ColSizeSpinBox->setRange(8, 1280 - m_nCaptureColStart);
	ui->RowStartSpinBox->setRange(0, ((1024 - m_nCaptureRowSize)<(1024 - 8)) ? (1024 - m_nCaptureRowSize) : (1024 - 8));
	ui->RowSizeSpinBox->setRange(8, 1024 - m_nCaptureRowStart);

	KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);
}

void CKSJSCZDemoMainWindow::OnColSizeChanged(int value)
{
	if (value >= 8)
	{
		m_nCaptureColStart = ui->ColStartSpinBox->value();
		m_nCaptureColSize = ui->ColSizeSpinBox->value();
		m_nCaptureRowStart = ui->RowStartSpinBox->value();
		m_nCaptureRowSize = ui->RowSizeSpinBox->value();

		ui->ColStartSpinBox->setRange(0, ((1280 - m_nCaptureColSize)<(1280 - 8)) ? (1280 - m_nCaptureColSize) : (1280 - 8));
		ui->ColSizeSpinBox->setRange(8, 1280 - m_nCaptureColStart);
		ui->RowStartSpinBox->setRange(0, ((1024 - m_nCaptureRowSize)<(1024 - 8)) ? (1024 - m_nCaptureRowSize) : (1024 - 8));
		ui->RowSizeSpinBox->setRange(8, 1024 - m_nCaptureRowStart);

		KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);
	}
}

void CKSJSCZDemoMainWindow::OnRowStartChanged(int value)
{
	m_nCaptureColStart = ui->ColStartSpinBox->value();
	m_nCaptureColSize = ui->ColSizeSpinBox->value();
	m_nCaptureRowStart = ui->RowStartSpinBox->value();
	m_nCaptureRowSize = ui->RowSizeSpinBox->value();

	ui->ColStartSpinBox->setRange(0, ((1280 - m_nCaptureColSize)<(1280 - 8)) ? (1280 - m_nCaptureColSize) : (1280 - 8));
	ui->ColSizeSpinBox->setRange(8, 1280 - m_nCaptureColStart);
	ui->RowStartSpinBox->setRange(0, ((1024 - m_nCaptureRowSize)<(1024 - 8)) ? (1024 - m_nCaptureRowSize) : (1024 - 8));
	ui->RowSizeSpinBox->setRange(8, 1024 - m_nCaptureRowStart);

	KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);
}

void CKSJSCZDemoMainWindow::OnRowSizeChanged(int value)
{
	if (value >= 8)
	{
		m_nCaptureColStart = ui->ColStartSpinBox->value();
		m_nCaptureColSize = ui->ColSizeSpinBox->value();
		m_nCaptureRowStart = ui->RowStartSpinBox->value();
		m_nCaptureRowSize = ui->RowSizeSpinBox->value();

		ui->ColStartSpinBox->setRange(0, ((1280 - m_nCaptureColSize)<(1280 - 8)) ? (1280 - m_nCaptureColSize) : (1280 - 8));
		ui->ColSizeSpinBox->setRange(8, 1280 - m_nCaptureColStart);
		ui->RowStartSpinBox->setRange(0, ((1024 - m_nCaptureRowSize)<(1024 - 8)) ? (1024 - m_nCaptureRowSize) : (1024 - 8));
		ui->RowSizeSpinBox->setRange(8, 1024 - m_nCaptureRowStart);

		KSJSCZ_SetCaptureFieldOfView(0, m_nCaptureColStart, m_nCaptureRowStart, m_nCaptureColSize, m_nCaptureRowSize);
	}
}

void CKSJSCZDemoMainWindow::OnRegAddressChanged(int value)
{
	ui->StaticText_RegAddress->setText(QString("0x%1").arg(value, 4, 16, QChar('0')));
}

void CKSJSCZDemoMainWindow::OnRegValueChanged(int value)
{
	ui->StaticText_RegValue->setText(QString("0x%1").arg(value, 8, 16, QChar('0')));
}

void CKSJSCZDemoMainWindow::OnReadReg()
{
	unsigned long ulRegValue;
	unsigned short usRegAddress = ui->RegAddressSpinBox->value();

	KSJSCZ_RdRegFPGA(0, usRegAddress, &ulRegValue);

	ui->RegValueSpinBox->setValue(ulRegValue);
}

void CKSJSCZDemoMainWindow::OnWriteReg()
{
	unsigned long ulRegValue = ui->RegValueSpinBox->value();
	unsigned short usRegAddress = ui->RegAddressSpinBox->value();

	KSJSCZ_WrRegFPGA(0, usRegAddress, ulRegValue);
}

void CKSJSCZDemoMainWindow::OnStartCapture()
{
	m_bIsCapturing = !m_bIsCapturing;

	ui->StartCapturePushButton->setText(m_bIsCapturing ? "Stop" : "Start");
}

