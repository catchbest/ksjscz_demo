


#include "ImageLabel.h"

CImageLabel::CImageLabel(QWidget* parent) : QLabel(parent)
{
	setMouseTracking(true);
}

CImageLabel::~CImageLabel()
{
}

void CImageLabel::mousePressEvent(QMouseEvent * e)
{
	emit sigmousePressEvent(e);
}

void CImageLabel::mouseReleaseEvent(QMouseEvent * e)
{
	emit sigmouseReleaseEvent(e);
}

void CImageLabel::mouseMoveEvent(QMouseEvent * e)
{
	emit sigmouseMoveEvent(e);
}

void CImageLabel::mouseDoubleClickEvent(QMouseEvent * e)
{
	emit sigmouseDoubleClickEvent(e);
}

void CImageLabel::wheelEvent(QWheelEvent * event)
{
	emit sigwheelEvent(event);
}
