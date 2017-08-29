
#include <stddef.h>
#include "KSJVBImageZoom.h"

CKSJVBImageZoom::CKSJVBImageZoom() :
m_nImageWidth(0),
m_nImageHeight(0),
m_nClientWidth(0),
m_nClientHeight(0),
m_eZoomMode(ZM_FITIMG),
m_fZoomScale(1.0f),
m_fSrcX(0.0f),
m_fSrcY(0.0f),
m_fSrcWidth(0.0f),
m_fSrcHeight(0.0f),
m_fDesX(0.0f),
m_fDesY(0.0f),
m_fDesWidth(0.0f),
m_fDesHeight(0.0f),
m_fOffsetX(0.0f),
m_fOffsetY(0.0f),
m_fDesImageWidth(0.0f),
m_fDesImageHeight(0.0f)
{

}

CKSJVBImageZoom::~CKSJVBImageZoom()
{

}

void CKSJVBImageZoom::SetImageSize(int nWidth, int nHeight)
{
	if (m_nImageWidth == nWidth && m_nImageHeight == nHeight) return;

	if (m_nImageWidth <= 0 || m_nImageHeight <= 0)
	{
		m_fOffsetX = (m_nClientWidth - nWidth) / 2.0f;
		m_fOffsetY = (m_nClientHeight - nHeight) / 2.0f;
	}

	m_nImageWidth = nWidth;
	m_nImageHeight = nHeight;

	if (m_nClientWidth > 0 && m_nClientHeight > 0 && m_nImageWidth > 0 && m_nImageHeight > 0)
	{
		if (m_eZoomMode == ZM_FITIMG)
		{
			if (m_nClientWidth > 0 && m_nClientHeight > 0 && m_nImageWidth > 0 && m_nImageHeight > 0)
			{
				float dx = (float)m_nClientWidth / m_nImageWidth;
				float dy = (float)m_nClientHeight / m_nImageHeight;

				UpdateScale((dx < dy) ? dx : dy, m_nClientWidth / 2, m_nClientHeight / 2);
			}
		}
		else
		{
			UpdateParams();
		}
	}
	else UpdateParams();
}

void CKSJVBImageZoom::SetClientSize(int nWidth, int nHeight)
{
	if (m_nClientWidth <= 0 || m_nClientHeight <= 0)
	{
		m_fOffsetX = (nWidth - m_nImageWidth) / 2.0f;
		m_fOffsetY = (nHeight - m_nImageHeight) / 2.0f;
	}

	m_nClientWidth = nWidth;
	m_nClientHeight = nHeight;

	if (m_nClientWidth > 0 && m_nClientHeight > 0 && m_nImageWidth > 0 && m_nImageHeight > 0)
	{
		if (m_eZoomMode == ZM_FITIMG)
		{
			if (m_nClientWidth > 0 && m_nClientHeight > 0 && m_nImageWidth > 0 && m_nImageHeight > 0)
			{
				float dx = (float)m_nClientWidth / m_nImageWidth;
				float dy = (float)m_nClientHeight / m_nImageHeight;

				UpdateScale((dx < dy) ? dx : dy, m_nClientWidth / 2, m_nClientHeight / 2);
			}
		}
		else
		{
			UpdateParams();
		}
	}
	else UpdateParams();
}

void CKSJVBImageZoom::SetZoomMode(KSJ_ZOOM_MODE mode)
{
	if (m_eZoomMode != mode)
	{
		m_eZoomMode = mode;

		if (m_nClientWidth > 0 && m_nClientHeight > 0 && m_nImageWidth > 0 && m_nImageHeight > 0)
		{
			if (m_eZoomMode == ZM_FITIMG)
			{
				if (m_nClientWidth > 0 && m_nClientHeight > 0 && m_nImageWidth > 0 && m_nImageHeight > 0)
				{
					float dx = (float)m_nClientWidth / m_nImageWidth;
					float dy = (float)m_nClientHeight / m_nImageHeight;

					UpdateScale((dx < dy) ? dx : dy, m_nClientWidth / 2, m_nClientHeight / 2);
				}
			}
		}
	}
}

KSJ_ZOOM_MODE CKSJVBImageZoom::GetZoomMode()
{
	return m_eZoomMode;
}

void CKSJVBImageZoom::ZoomOut(int nOperateX, int nOperateY)
{
	m_eZoomMode = ZM_ZOOM;
	
	if (m_fZoomScale>0.1f) UpdateScale(m_fZoomScale * 0.95f, nOperateX, nOperateY);
}

void CKSJVBImageZoom::ZoomIn(int nOperateX, int nOperateY)
{
	m_eZoomMode = ZM_ZOOM;
	
	if (m_fZoomScale < 20.0f) UpdateScale(m_fZoomScale / 0.95f, nOperateX, nOperateY);
}

void CKSJVBImageZoom::Move(int nDivX, int nDivY)
{
	m_fOffsetX += nDivX;
	m_fOffsetY += nDivY;

	ViewFieldRectify();
}

void CKSJVBImageZoom::ViewFieldRectify()
{
	if (m_fDesImageWidth <= m_nClientWidth)
	{
		m_fOffsetX = (m_nClientWidth - m_fDesImageWidth) / 2.0f;

		m_fSrcX = 0.0f;
		m_fSrcWidth = m_nImageWidth;

		m_fDesX = m_fOffsetX;
		m_fDesWidth = m_fDesImageWidth;
	}
	else
	{
		if (m_fOffsetX > 0) m_fOffsetX = 0;
		else if ((m_fDesImageWidth + m_fOffsetX) < m_nClientWidth) m_fOffsetX = m_nClientWidth - m_fDesImageWidth;

		m_fDesX = 0.0f;
		m_fDesWidth = m_nClientWidth;

		m_fSrcX = (m_fDesX - m_fOffsetX) / m_fZoomScale;
		m_fSrcWidth = m_fDesWidth / m_fZoomScale;
	}

	if (m_fDesImageHeight <= m_nClientHeight)
	{
		m_fOffsetY = (m_nClientHeight - m_fDesImageHeight) / 2;

		m_fSrcY = 0;
		m_fSrcHeight = m_nImageHeight;

		m_fDesY = m_fOffsetY;
		m_fDesHeight = m_fDesImageHeight;
	}
	else
	{
		if (m_fOffsetY > 0) m_fOffsetY = 0;
		else if ((m_fDesImageHeight + m_fOffsetY) < m_nClientHeight) m_fOffsetY = m_nClientHeight - m_fDesImageHeight;

		m_fDesY = 0.0f;
		m_fDesHeight = m_nClientHeight;

		m_fSrcY = (m_fDesY - m_fOffsetY) / m_fZoomScale;
		m_fSrcHeight = m_fDesHeight / m_fZoomScale;
	}
}

void CKSJVBImageZoom::UpdateParams()
{
	m_fDesImageWidth = m_fZoomScale * m_nImageWidth;
	m_fDesImageHeight = m_fZoomScale * m_nImageHeight;

	ViewFieldRectify();
}

void CKSJVBImageZoom::UpdateScale(float dNewScale, int nOperateX, int nOperateY)
{
	m_fOffsetX = nOperateX + (m_fOffsetX - nOperateX) / m_fZoomScale * dNewScale;
	m_fOffsetY = nOperateY + (m_fOffsetY - nOperateY) / m_fZoomScale * dNewScale;

	m_fZoomScale = dNewScale;

	m_fDesImageWidth = m_fZoomScale*m_nImageWidth;
	m_fDesImageHeight = m_fZoomScale*m_nImageHeight;

	ViewFieldRectify();
}

void CKSJVBImageZoom::GetImageShowPosition(int& x, int& y, int& w, int& h)
{
	x = m_fOffsetX;
	y = m_fOffsetY;
	w = m_fDesImageWidth + m_fOffsetX - x;
	h = m_fDesImageHeight + m_fOffsetY - y;
}

void CKSJVBImageZoom::MapPointClientToImage(float fClientX, float fClientY, float& fImageX, float& fImageY) const
{
	fImageX = (fClientX - m_fOffsetX) / m_fZoomScale;
	fImageY = (fClientY - m_fOffsetY) / m_fZoomScale;
}
