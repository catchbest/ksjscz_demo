#pragma once

#include "QtGui/QLabel"

class CKsjScrollbar;

class CImageLabel : public QLabel
{
	Q_OBJECT

public:
	CImageLabel(QWidget* parent = NULL);
	~CImageLabel();

signals:                                     //�Զ����ź�
	void explains();            //����Ҫ�Զ���ۺ��ź�, explains�ź��Ǳ����
	void sigmousePressEvent(QMouseEvent * e);
	void sigmouseReleaseEvent(QMouseEvent * e);
	void sigmouseMoveEvent(QMouseEvent * e);
	void sigmouseDoubleClickEvent(QMouseEvent * e);
	void sigwheelEvent(QWheelEvent * event);

protected:
	virtual void mousePressEvent(QMouseEvent * e);
	virtual void mouseReleaseEvent(QMouseEvent * e);
	virtual void mouseMoveEvent(QMouseEvent * e);
	virtual void mouseDoubleClickEvent(QMouseEvent * e);
	virtual void wheelEvent(QWheelEvent * event);
};
