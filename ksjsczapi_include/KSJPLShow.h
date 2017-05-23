#ifndef __KSJ_QT_API_H___
#define __KSJ_QT_API_H___

#include <unistd.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef int KSJQT_API;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KSJQTAPI函数返回代码
enum KSJQT_ERROR_LIST
{
	KSJQT_ERR_SUCCESS             = 0,
	KSJQT_ERR_ERROR               = -1001,
	KSJQT_ERR_INVALID_PARAMETER   = -1009,

	KSJQT_ERR_CUSTOM_ID           = -10000
};

typedef void (*ksjButtonCallback)(void);
typedef void (*ksjTrackbarCallback)(int pos);
typedef void (*ksjSpinBoxCallback)(int pos);
typedef void (*ksjComboBoxCallback)(int pos);
typedef void (*ksjGroupBoxCallback)(void *userdata);

/*
* 初始化显示
*/
KSJQT_API KSJQT_Open(void);

/*
* 关闭显示
*/
KSJQT_API KSJQT_Close(void);

/*
* 指定显示图像的label 的尺寸
* (unXoffset,unYoffset) 是label 距显示器左上角的偏移
*/
KSJQT_API KSJQT_SetVideoWidgetPos(unsigned int unXoffset, unsigned int unYoffset, unsigned int unWidgetWidth, unsigned int unWidgetHeight);

/*
* 指定图像的显示尺寸
* (nXoffset,nYoffset) 是图像距显示label左上角 的偏移
*/
KSJQT_API KSJQT_SetPosition(int nXoffset, int nYoffset, unsigned int unDisplayWidth, unsigned int unDisplayHeight);

/*
* 显示一帧图像
*/
KSJQT_API KSJQT_Show(unsigned char *pDataBuffer, unsigned int unRawWidth, unsigned int unRawHeight, unsigned int unBitCount);

//KSJQT_BitBlt(int x, int y, int w, int h, unsigned char* pData, int nSrcPicW, int nSrcPicH, int nSrcX = 0, int nSrcY = 0, int nSrcW = -1, int nSrcH = -1);

/*
* 需要显示时，由固定物理内存池申请内存
*/
void *KSJ_Malloc(size_t size);

/*
* 释放物理内存池中的一块内存
*/
void KSJ_Free(void *ptr);


#ifdef __cplusplus
}
#endif

#endif
