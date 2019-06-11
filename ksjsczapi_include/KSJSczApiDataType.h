#ifndef _KSJ_SCZ_API_DATA_TYPE_H__
#define _KSJ_SCZ_API_DATA_TYPE_H__

#ifndef HANDLE
    typedef void* HANDLE;
#endif

#ifndef NULL
#define NULL 0
#endif

typedef void(*KSJSCZ_TRIGGER_CALLBACK)(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext);

#pragma pack ( 1 )
typedef struct _tagUSBCmd
{
	unsigned char  bmRequest;
	unsigned char  bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;					// 表示发送或接受数据的长度
}USBCMD, *PUSBCMD;
#pragma pack ( 8 )

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
	KSJSCZ_ST_E130C,
	KSJSCZ_ST_UNKNOWN = -1
};

enum KSJ_PARAM
{
	KSJ_EXPOSURE = 0,        // Exposure Time (ms)
	KSJ_RED,                 // Red Gain, for line scan sensor map to seg0, for ccd map to KSJ_VGAGAIN
	KSJ_GREEN,               // Green Gain, for line scan sensor map to seg1, for ccd map to KSJ_LAMPLEVEL
	KSJ_BLUE,                // Blue Gain, for CCD map to KSJ_CDSGAIN
	KSJ_GAMMA,               // Gamma
	KSJ_PREVIEW_COLUMNSTART, // Preview Col Start
	KSJ_PREVIEW_ROWSTART,    // Preview Row Start
	KSJ_CAPTURE_COLUMNSTART, // Capture Col Start
	KSJ_CAPTURE_ROWSTART,    // Capture Row Start
	KSJ_HORIZONTALBLANK,     // Horizontal Blank
	KSJ_VERTICALBLANK,       // Vertical Blank
	KSJ_FLIP,                // Flip
	KSJ_BIN,                 // Binning
	KSJ_MIRROR,              // Mirror
	KSJ_CONTRAST,            // Contrast
	KSJ_BRIGHTNESS,          // Brightness
	KSJ_VGAGAIN,             // VGA Gain(CCD)
	KSJ_CLAMPLEVEL,          // Clamp Level(CCD)
	KSJ_CDSGAIN,             // CDS Gain(CCD)
	KSJ_RED_SHIFT,           // Not Use
	KSJ_GREEN_SHIFT,         // Not Use
	KSJ_BLUE_SHIFT,          // Not Use
	KSJ_COMPANDING,          // Companding
	KSJ_EXPOSURE_LINES,      // Exposure Lines
	KSJ_SATURATION,          // Saturation
	KSJ_TRIGGERDELAY,              // Trigger Delay Step = 100uS
	KSJ_STROBEDELAY,               // Not Use
	KSJ_TRIGGER_MODE,              // Trigger Mode
	KSJ_TRIGGER_METHOD,            // Trigger Method
	KSJ_BLACKLEVEL,                // Black Level
	KSJ_BLACKLEVEL_THRESHOLD_AUTO, // Black Level Threshold Auto
	KSJ_BLACKLEVEL_THRESHOLD_LO,   // Black Level Low Threshold
	KSJ_BLACKLEVEL_THRESHOLD_HI    // Black Level High Threshold
};

enum KSJ_ADDRESSMODE
{
	KSJ_SKIPNONE = 0,
	KSJ_SKIP2,
	KSJ_SKIP3,
	KSJ_SKIP4,
	KSJ_SKIP8
};

enum KSJ_PREVIEWMODE
{
	PM_RAWDATA,
	PM_RGBDATA
};

enum    KSJ_PREVIEWSTATUS
{
	PS_STOP,
	PS_START,
	PS_PAUSE
};

enum KSJ_WB_MODE
{
	KSJ_WB_DISABLE,
	KSJ_SWB_PRESETTINGS,
	KSJ_SWB_AUTO_ONCE,
	KSJ_SWB_AUTO_CONITNUOUS,
	KSJ_SWB_MANUAL,
	KSJ_HWB_PRESETTINGS,
	KSJ_HWB_AUTO_ONCE,
	KSJ_HWB_AUTO_CONITNUOUS,
	KSJ_HWB_MANUAL
};

enum KSJ_COLOR_TEMPRATURE
{
	KSJ_CT_5000K,
	KSJ_CT_6500K,
	KSJ_CT_2800K
};


enum KSJ_AWB_TYPE{ KSJ_AWB_ONCE, KSJ_AWB_2800K, KSJ_AWB_5000K, KSJ_AWB_6500K };
enum KSJ_SHARPNESS_TYPE{ KSJ_SHARPNESS_OFF, KSJ_SHARPNESS_MODE1, KSJ_SHARPNESS_MODE2 };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SCCM - Software Color Correction Matrix; HCCM - Hardware Color Correction Matrix
enum KSJ_CCM_MODE
{
	KSJ_CCM_DISABLE,
	KSJ_SCCM_PRESETTINGS,
	KSJ_SCCM_MANUAL,
	KSJ_HCCM_PRESETTINGS,
	KSJ_HCCM_MANUAL
};

typedef void(*KSJ_WB_CALLBACK)(float fMatrix[3], void *lpContext);
typedef void(*KSJ_WB_CALLBACK_EX)(float fMatrixR, float fMatrixG, float fMatrixB, void *lpContext);

enum KSJ_TRIGGERMODE
{
	KSJ_TRIGGER_INTERNAL,
	KSJ_TRIGGER_EXTERNAL,
	KSJ_TRIGGER_SOFTWARE,
	KSJ_TRIGGER_FIXFRAMERATE
};

enum KSJ_TRIGGERSTATUS
{
	KSJ_NO,
	KSJ_HAVE
};

enum KSJ_TRIGGERMETHOD
{
	KSJ_TRIGGER_FALLINGEDGE,
	KSJ_TRIGGER_RISINGEDGE,
	KSJ_TRIGGER_HIGHLEVEL,
	KSJ_TRIGGER_LOWLEVEL
};

// 灵敏度模式设置（使用截取8位方式）
enum KSJ_SENSITIVITYMODE
{
	KSJ_LOW = 0,
	KSJ_MID,
	KSJ_HIGH,
	KSJ_HIGHER,
	KSJ_HIGHEST
};

// Bayer Mode
enum KSJ_BAYERMODE
{
	KSJ_BGGR_BGR24 = 0,
	KSJ_GRBG_BGR24,
	KSJ_RGGB_BGR24,
	KSJ_GBRG_BGR24,
	KSJ_BGGR_BGR24_FLIP,
	KSJ_GRBG_BGR24_FLIP,
	KSJ_RGGB_BGR24_FLIP,
	KSJ_GBRG_BGR24_FLIP,
	KSJ_BGGR_BGR32,
	KSJ_GRBG_BGR32,
	KSJ_RGGB_BGR32,
	KSJ_GBRG_BGR32,
	KSJ_BGGR_BGR32_FLIP,
	KSJ_GRBG_BGR32_FLIP,
	KSJ_RGGB_BGR32_FLIP,
	KSJ_GBRG_BGR32_FLIP,
	KSJ_BGGR_GRAY8,
	KSJ_GRBG_GRAY8,
	KSJ_RGGB_GRAY8,
	KSJ_GBRG_GRAY8,
	KSJ_BGGR_GRAY8_FLIP,
	KSJ_GRBG_GRAY8_FLIP,
	KSJ_RGGB_GRAY8_FLIP,
	KSJ_GBRG_GRAY8_FLIP
};

// Bayer Filter Algorithm 
enum KSJ_FILTERMODE
{
	KSJ_NEARESTNEIGHBOR,
	KSJ_BILINEAR,
	KSJ_SMOOTHHUE,
	KSJ_EDGESENSING,
	KSJ_LAPLACIAN,
	KSJ_FASTBILINEAR
};

enum KSJ_EEPROM_TYPE { KSJ_24LC64, KSJ_24LC1024, KSJ_24LC128 };

enum KSJ_AE_STATUS
{
	KSJ_AE_ONCE_SUCCESS = 0,
	KSJ_AE_ONCE_FAIL_MAX_COUNT,
	KSJ_AE_ONCE_FAIL_WAVE,
	KSJ_AE_ONCE_FAIL_OVER_RANGE,
	KSJ_AE_DOING,
	KSJ_AE_CONTINUE_SUCCESS,
	KSJ_AE_CONTINUE_FAIL_WAVE,
	KSJ_AE_CONTINUE_FAIL_OVER_RANGE
};

// Auto Exposure Ex Callback, Call when AE Doing, Success, Fail.
typedef void(*KSJ_AECALLBACKEX)(KSJ_AE_STATUS Status, int nExpsoureTimeMs, void *lpContext);
// Auto Exposure Callback, Call when AE Finish.
typedef void(*KSJ_AECALLBACK)(bool bSuccess, int nResult, void *lpContext);
// 聚焦评估回调函数, nValue为返回的评估值
typedef void(*KSJ_AFCALLBACK)(int nValue, void *lpContext);

#endif