#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include <QMutex>
#include <QDialog>


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
	void OnColStartChanged(int);
	void OnColSizeChanged(int);
	void OnRowStartChanged(int);
	void OnRowSizeChanged(int);
	void OnRegAddressChanged(int);
	void OnRegValueChanged(int);
	void OnReadReg();
	void OnWriteReg();
	void OnReadGpio();
	void OnWriteGpio();
	void OnStartCapture();
	void OnTrigerDelayChanged(int);

protected:
	virtual void paintEvent(QPaintEvent *);

protected:
	int StartCaptureThread();
	int KillCaptureThread();

public:
	bool m_bIsCapturing;
	bool m_bStopCaptureThread;

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

	int m_nCaptureColStart;
	int m_nCaptureColSize;
	int m_nCaptureRowStart;
	int m_nCaptureRowSize;

protected:
	void UpdateUiWithCameraSetting();
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
