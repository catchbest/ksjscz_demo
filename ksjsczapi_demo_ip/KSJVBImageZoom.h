#ifndef _KSJVBBASE_IMAGEZOOM_H__
#define _KSJVBBASE_IMAGEZOOM_H__

enum KSJ_ZOOM_MODE { ZM_FITIMG, ZM_ZOOM };

class CKSJVBImageZoom
{
public:
	CKSJVBImageZoom();
	virtual ~CKSJVBImageZoom();

public:
	virtual void SetImageSize(int nWidth, int nHeight);
	virtual void SetClientSize(int nWidth, int nHeight);

	virtual void SetZoomMode(KSJ_ZOOM_MODE mode);
	virtual KSJ_ZOOM_MODE GetZoomMode();

	//所有操作都是以平面坐标为准
	virtual void ZoomOut(int nOperateX, int nOperateY);
	virtual void ZoomIn(int nOperateX, int nOperateY);

	virtual void Move(int nDivX, int nDivY);

	virtual void MapPointClientToImage(float fClientX, float fClientY, float& fImageX, float& fImageY) const;

	virtual void GetImageShowPosition(int& x, int& y, int& w, int& h);

protected:
	void UpdateParams();                                                     //修改各个参数以后,重新计算位置
	void UpdateScale(float dNewScale, int nOperateX, int nOperateY);         //修改放大比例参数以后,重新修改参数
	void ViewFieldRectify();                                                 //修正视觉参数

protected:
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nClientWidth;
	int m_nClientHeight;

	float m_fZoomScale;
	KSJ_ZOOM_MODE m_eZoomMode;

	float m_fDesX, m_fDesY, m_fDesWidth, m_fDesHeight;
	float m_fSrcX, m_fSrcY, m_fSrcWidth, m_fSrcHeight;

	float m_fOffsetX, m_fOffsetY, m_fDesImageWidth, m_fDesImageHeight;
};

#endif