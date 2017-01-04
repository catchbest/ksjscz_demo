#ifndef __KSJ_QT_API_H___
#define __KSJ_QT_API_H___



#ifdef __cplusplus
extern "C" {
#endif

typedef int KSJQT_API;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KSJQTAPIº¯Êý·µ»Ø´úÂë
enum KSJQT_ERROR_LIST
{
	KSJQT_ERR_SUCCESS             = 0,
	KSJQT_ERR_ERROR               = -1001,
	KSJQT_ERR_INVALID_PARAMETER   = -1009,

	KSJQT_ERR_CUSTOM_ID           = -10000
};

KSJQT_API KSJQT_Open(void);
KSJQT_API KSJQT_Close(void);
KSJQT_API KSJQT_Show(unsigned char *pDataBuffer, unsigned int unRawWidth, unsigned int unRawHeight, unsigned int unBitCount);
KSJQT_API KSJQT_SetPosition(int nXoffset, int nYoffset, unsigned int unDisplayWidth, unsigned int unDisplayHeight);

#ifdef __cplusplus
}
#endif

#endif
