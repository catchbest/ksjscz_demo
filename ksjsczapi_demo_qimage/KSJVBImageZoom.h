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

	virtual int GetClientWidth() const { return m_nClientWidth; }
	virtual int GetClientHeight() const { return m_nClientHeight; }

	virtual void SetZoomMode(KSJ_ZOOM_MODE mode);
	virtual KSJ_ZOOM_MODE GetZoomMode();

	//���в���������ƽ������Ϊ׼
	virtual void ZoomOut(int nOperateX, int nOperateY);
	virtual void ZoomIn(int nOperateX, int nOperateY);

	virtual void Move(int nDivX, int nDivY);

	virtual void SetOffset(int nOffsetX, int nOffsetY);
	virtual void GetOffset(int& nOffsetX, int& nOffsetY);

	virtual void GetImageShowPosition(int& x, int& y, int& w, int& h);
	virtual void GetValidShowPosition(int& nImageSrcX, int& nImageSrcY, int& nImageWidth, int& nImageHeight, int& nClientDesX, int& nClientDesY, int& nClientWidth, int& nClientHeight);

protected:
	void UpdateParams();                                                     //�޸ĸ��������Ժ�,���¼���λ��
	void UpdateScale(float dNewScale, int nOperateX, int nOperateY);         //�޸ķŴ���������Ժ�,�����޸Ĳ���
	void ViewFieldRectify();                                                 //�����Ӿ�����

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