#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include "QtCore/QTimer"
#include "QtGui/QDialog"
#include "QtGui/QLabel"
#include "QtGui/QScrollArea"
#include "QtGui/QMatrix"
#include "KSJVBImageZoom.h"
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
	void OnHorScrollbar(int value);
	void OnVerScrollbar(int value);


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
	bool m_bStopCaptureThread;
	unsigned long m_nCaptureInterruptThreadId;

protected:
	friend void* ThreadForCaptureData(void *arg);

protected:
	void ResetScrollerInfo();
	void ConvertToQImage(unsigned char* pImageData, int w, int h);

public:
	virtual void ZoomIn();
	virtual void ZoomOut();
	virtual void ZoomIn(int nClientX, int nClientY);
	virtual void ZoomOut(int nClientX, int nClientY);
	virtual void SetZoomMode(KSJ_ZOOM_MODE mode);

protected:
	QImage* m_pImage;

	QRect  m_rcClient;
	QPoint m_ptLastMouse;

	int m_nImageLastWidth;
	int m_nImageLastHeight;

	CKSJVBImageZoom* m_pImageZoomer;
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
