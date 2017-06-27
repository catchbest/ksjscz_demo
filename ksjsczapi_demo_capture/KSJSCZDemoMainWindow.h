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

protected slots:
	void OnStartCapture();

protected:
	virtual void paintEvent(QPaintEvent *);

protected:
	int StartCaptureThread();
	int KillCaptureThread();

protected:
	bool m_bIsCapturing;
	bool m_bStopCaptureThread;
	unsigned long m_nCaptureInterruptThreadId;

protected:
	friend void* ThreadForCaptureData(void *arg);
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
