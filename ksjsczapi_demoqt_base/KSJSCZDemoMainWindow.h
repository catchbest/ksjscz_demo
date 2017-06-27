#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include "QtCore/QTimer"
#include "QtGui/QDialog"
#include "QtGui/QMatrix"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"


namespace Ui { class KSJSCZDemoMainWindow; }

class CKSJSCZDemoMainWindow : public QDialog
{
	Q_OBJECT

public:
	explicit CKSJSCZDemoMainWindow(QWidget *parent = 0);
	~CKSJSCZDemoMainWindow();

private:
	Ui::KSJSCZDemoMainWindow *ui;

protected:
	void changeEvent(QEvent * event);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);

protected slots:
	void OnTriggerModeChanged(int);
	void OnExpTimerChanged(double);
	void OnExpLinesChanged(int);
	void OnGainChanged(int);
	void OnReadReg();
	void OnWriteReg();
	void OnReadGpio();
	void OnSetFov();
	void OnTriggerDelayChanged(int);
	void OnProcessDataChkBoxStateChanged(int);
	void OnMirrorChkBoxStateChanged(int);
	void OnFlipChkBoxStateChanged(int);
	void OnStartCapture();

	void OnEan13ChkBoxStateChanged(int);
	void OnEan8ChkBoxStateChanged(int);
	void OnUPCAChkBoxStateChanged(int);
	void OnUPCEChkBoxStateChanged(int);
	void OnISBN10ChkBoxStateChanged(int);
	void OnISBN13ChkBoxStateChanged(int);
	void OnI25ChkBoxStateChanged(int);
	void OnCODE39ChkBoxStateChanged(int);
	void OnCODE128ChkBoxStateChanged(int);
	void OnPDF417ChkBoxStateChanged(int);
	void OnQRCODEChkBoxStateChanged(int);
	void OnDensitySpinBoxChanged(int);

	void OnALedCheckBoxChanged(int);
	void OnBLedCheckBoxChanged(int);
	void OnIO1CheckBoxChanged(int);
	void OnIO2CheckBoxChanged(int);
	void OnIO3CheckBoxChanged(int);

	void OnTimerFrameRate();

protected:
	virtual void paintEvent(QPaintEvent *);
private:
	QTimer* m_pTimerFrameRate;

	int  m_nTimeTick;
	int  m_nCaptureCountPre;
protected:
	int StartCaptureThread();
	int KillCaptureThread();

	void ParseZbar(unsigned char *pData, int nWidth, int nHeight);
	void SingleCaptureCompleted();

protected:
	bool m_bIsMirror;
	bool m_bIsFlip;

	bool m_bIsCapturing;
	bool m_bParseZbarDemo;
	bool m_bStopCaptureThread;
	
	KSJSCZ_TRIGGER_MODE m_nTriggerMode;

	int  m_nCaptureCount;
	int  m_nParseZbarCount;
	int  m_nParseZbarFailedCount;

	bool m_bDcodeEAN13;
	bool m_bDcodeEAN8;
	bool m_bDcodeUPCA;
	bool m_bDcodeUPCE;
	bool m_bDcodeISBN10;
	bool m_bDcodeISBN13;
	bool m_bDcodeI25;
	bool m_bDcodeCODE39;
	bool m_bDcodeCODE128;
	bool m_bDcodePDF417;
	bool m_bDcodeQRCODE;

	int m_nDensity;

	bool m_bALedShine;
	bool m_bBLedShine;
	unsigned char m_ucLedShineValue;

protected:
	unsigned long m_nCaptureInterruptThreadId;

protected:
	int m_nVideoWidgetLeft;      // 图像显示的Widget位置
	int m_nVideoWidgetTop;
	int m_nVideoWidgetWidth;
	int m_nVideoWidgetHeight;

	int m_nImagePositionLeft;      // 图像相对VideoWidget的位置
	int m_nImagePositionTop;
	int m_nImagePositionWidth;
	int m_nImagePositionHeight;

	int m_nExpLines;
	int m_nGain;
	int m_nDelay;

	int m_nCaptureColStart;
	int m_nCaptureColSize;
	int m_nCaptureRowStart;
	int m_nCaptureRowSize;

protected:
	void SaveUserParams();
	void LoadUserParams();
	void ResetShowPositions();
	void UpdateUiSetting();

protected:
	friend void* ThreadForCaptureData(void *arg);
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
