#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include "QtCore/QTimer"
#include "QtGui/QDialog"
#include "QtGui/QMatrix"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
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
	void OnStopCapture();
	void OnThresholdChkBoxStateChanged(int);

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent * e);
	virtual void mouseReleaseEvent(QMouseEvent * e);
	virtual void mouseMoveEvent(QMouseEvent * e);
	virtual void mouseDoubleClickEvent(QMouseEvent * e);
	virtual void wheelEvent(QWheelEvent * event);

protected:
	int StartCaptureThread();
	int KillCaptureThread();

protected:
	bool m_bIsCapturing;
	bool m_bThresholdImage;
	bool m_bStopCaptureThread;
	unsigned long m_nCaptureInterruptThreadId;

	int  m_nVideoMemorySize;
	unsigned char* m_pVideoMemory;

	int m_nImageWidth;
	int m_nImageHeight;
	int m_nImageBitCount;

protected:
	void CaptureData(unsigned char* pImage, int w, int h, int bitcount);

protected:
	friend void* ThreadForCaptureData(void *arg);

};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
