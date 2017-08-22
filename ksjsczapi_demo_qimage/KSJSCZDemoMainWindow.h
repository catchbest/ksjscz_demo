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
	// 采集到的图像
	QImage* m_pImage;

	// 保留图像显示位置的信息
	QRect  m_rcClient;
	// 鼠标上一次的位置
	QPoint m_ptLastMouse;

	// 原来图像的大小
	int m_nImageLastWidth;
	int m_nImageLastHeight;

	//这个是用来计算放大缩小位置的类
	CKSJVBImageZoom* m_pImageZoomer;
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
