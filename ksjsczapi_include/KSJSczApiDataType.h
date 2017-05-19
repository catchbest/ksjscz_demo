#ifndef _KSJ_SCZ_API_DATA_TYPE_H__
#define _KSJ_SCZ_API_DATA_TYPE_H__

#ifndef HANDLE
    typedef void* HANDLE;
#endif

#ifndef NULL
#define NULL 0
#endif

typedef void(*KSJSCZ_TRIGGER_CALLBACK)(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext);


enum KSJSCZ_DEVICE_TYPE
{
	KSJSCZ15_GE_X1200C = 0,
	KSJSCZ15_GE_E130M,
	KSJSCZ_DT_UNKNOWN = -1,
};

enum KSJSCZ_SENSOR_TYPE
{
	KSJSCZ_ST_X1200C = 0,
	KSJSCZ_ST_E130M,
	KSJSCZ_ST_UNKNOWN = -1
};

// Skip Mode (Address Mode)
enum KSJ_ADDRESSMODE
{
	KSJ_SKIPNONE = 0,
	KSJ_SKIP2,
	KSJ_SKIP3,
	KSJ_SKIP4,
	KSJ_SKIP8
};

// Trigger Mode
enum KSJSCZ_TRIGGER_MODE
{
	KSJSCZ_TM_CMD_CONTINUE,
	KSJSCZ_TM_CMD_SINGLE,
	KSJSCZ_TM_EXT_LEVEL_HI,
	KSJSCZ_TM_EXT_LEVEL_LO,
	KSJSCZ_TM_EXT_EDGE_POS,
	KSJSCZ_TM_EXT_EDGE_NEG,
};


#endif