#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include "QtCore/QTimer"
#include "QtGui/QDialog"
#include "QtGui/QLabel"
#include "QtGui/QScrollArea"
#include "QtGui/QMatrix"
#include "ImageLabel.h"
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

	virtual void smousePressEvent(QMouseEvent * e);
	virtual void smouseReleaseEvent(QMouseEvent * e);
	virtual void smouseMoveEvent(QMouseEvent * e);
	virtual void smouseDoubleClickEvent(QMouseEvent * e);
	virtual void swheelEvent(QWheelEvent * event);

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void resizeEvent(QResizeEvent * event);

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
	void ConvertToQImage(unsigned char* pImageData, int w, int h);

protected:
	QImage* m_pImage;
	QPixmap m_pixmapToShow;

	CImageLabel *m_pImageShowLabel;
	QScrollArea *m_pImageWidgetScroll;

	int m_nShowWidth;
	int m_nShowHeight;

	QPoint m_ptLastMouse;
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
