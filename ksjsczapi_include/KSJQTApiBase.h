#ifndef __KSJ_QT_API_H___
#define __KSJ_QT_API_H___

#include <unistd.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef int KSJQT_API;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KSJQTAPI�������ش���
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
* ��ʼ����ʾ
*/
KSJQT_API KSJQT_Open(void);

/*
* �ر���ʾ
*/
KSJQT_API KSJQT_Close(void);

/*
* ָ����ʾͼ���label �ĳߴ�
* (unXoffset,unYoffset) ��label ����ʾ�����Ͻǵ�ƫ��
*/
KSJQT_API KSJQT_SetVideoWidgetPos(unsigned int unXoffset, unsigned int unYoffset, unsigned int unWidgetWidth, unsigned int unWidgetHeight);

/*
* ָ��ͼ�����ʾ�ߴ�
* (nXoffset,nYoffset) ��ͼ�����ʾlabel���Ͻ� ��ƫ��
*/
KSJQT_API KSJQT_SetPosition(int nXoffset, int nYoffset, unsigned int unDisplayWidth, unsigned int unDisplayHeight);

/*
* ��ʾһ֡ͼ��
*/
KSJQT_API KSJQT_Show(unsigned char *pDataBuffer, unsigned int unRawWidth, unsigned int unRawHeight, unsigned int unBitCount);

/*
* ����һ��slider �� button����Ͽؼ�������Ϊbar
* ����:
*            pBarName - bar ������
*            pnValue - slider ��ǰֵ
*            nCount - slider ���ֵ
*            callback - ���û���д��ʵ�������������
*            userdata - ��չ��������Ϊ NULL
*/
KSJQT_API KSJQT_CreateTrackBar(const char* pBarName, int* pnValue, int nCount, ksjTrackbarCallback callback, void* userdata);

/*
* ����һ��SpinBox �ؼ�
* ����:
*            pBoxName - box ������
*            pnValue - box ��ǰֵ
*            nCount - box ���ֵ
*            callback - ���û���д��ʵ�������������
*            userdata - ��չ��������Ϊ NULL
*/
KSJQT_API KSJQT_CreateSpinBox(const char* pBoxName, int* pnValue, int nCount, ksjSpinBoxCallback callback, void* userdata);

/*
* ����һ��ComboBox �ؼ�
* ����:
*            pBoxName - box ������
*            pnValue - box ��ǰֵ
*            nCount - box ���ֵ
*            array - Ҫ��ʾ��box�е��ַ���
*            callback - ���û���д��ʵ�������������( ���紥��ģʽ����)
*            userdata - ��չ��������Ϊ NULL
*/
KSJQT_API KSJQT_CreateComboBox(const char* pBoxName, int* pnValue, int nCount, const char **array, ksjComboBoxCallback callback, void* userdata);

KSJQT_API KSJQT_CreateButton(const char* pButtonName, ksjButtonCallback callback, void* userdata);

/*
* ����һ�������ʾ��Ͽ�
* ����:
*            pReportName - ��Ͽ� ������
*            callback - ���û���д���ṩ�����ֵ�����ܽ���֡�����ɹ�����֡��
*/
KSJQT_API KSJQT_CreateGroupBox(const char* pBoxName, ksjGroupBoxCallback callback);


KSJQT_API KSJQT_CreateStaticText(const char* pText);

/*
* ��Ҫ��ʾʱ���ɹ̶������ڴ�������ڴ�
*/
void *KSJ_Malloc(size_t size);

/*
* �ͷ������ڴ���е�һ���ڴ�
*/
void KSJ_Free(void *ptr);


#ifdef __cplusplus
}
#endif

#endif
