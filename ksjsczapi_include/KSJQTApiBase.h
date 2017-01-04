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

/*
* 创建一个slider 与 button的组合控件，命名为bar
* 参数:
*            pBarName - bar 的名称
*            pnValue - slider 当前值
*            nCount - slider 最大值
*            callback - 由用户填写，实现相机参数控制
*            userdata - 拓展参数，可为 NULL
*/
KSJQT_API KSJQT_CreateTrackBar(const char* pBarName, int* pnValue, int nCount, ksjTrackbarCallback callback, void* userdata);

/*
* 创建一个SpinBox 控件
* 参数:
*            pBoxName - box 的名称
*            pnValue - box 当前值
*            nCount - box 最大值
*            callback - 由用户填写，实现相机参数控制
*            userdata - 拓展参数，可为 NULL
*/
KSJQT_API KSJQT_CreateSpinBox(const char* pBoxName, int* pnValue, int nCount, ksjSpinBoxCallback callback, void* userdata);

/*
* 创建一个ComboBox 控件
* 参数:
*            pBoxName - box 的名称
*            pnValue - box 当前值
*            nCount - box 最大值
*            array - 要显示在box中的字符串
*            callback - 由用户填写，实现相机参数控制( 比如触发模式控制)
*            userdata - 拓展参数，可为 NULL
*/
KSJQT_API KSJQT_CreateComboBox(const char* pBoxName, int* pnValue, int nCount, const char **array, ksjComboBoxCallback callback, void* userdata);

KSJQT_API KSJQT_CreateButton(const char* pButtonName, ksjButtonCallback callback, void* userdata);

/*
* 创建一个结果显示组合框
* 参数:
*            pReportName - 组合框 的名称
*            callback - 由用户填写，提供结果数值，如总解码帧数及成功解码帧数
*/
KSJQT_API KSJQT_CreateGroupBox(const char* pBoxName, ksjGroupBoxCallback callback);


KSJQT_API KSJQT_CreateStaticText(const char* pText);

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
