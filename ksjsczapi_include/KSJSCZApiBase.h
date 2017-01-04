#ifndef __KSJ_SCZ_API_H___
#define __KSJ_SCZ_API_H___

#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>
#include <stdio.h>
#include <sys/vfs.h>
#include <sys/file.h>
#include <stdlib.h>

#if defined (_WIN32)
#  ifdef KSJSCZDLL
#    define KSJSCZ_IMPORT_EXPORT __declspec(dllexport)
#  else
#    define KSJSCZ_IMPORT_EXPORT __declspec(dllimport)
#  endif
#  if defined (_M_IX86) || defined (__i386__)
#    define KSJSCZ_CALLTYPE __stdcall
#  else
#    define KSJSCZ_CALLTYPE  
#  endif
#  ifndef EXTERN_C
#    define EXTERN_C extern "C"
#  endif

#elif defined (__GNUC__) && (__GNUC__ >= 4) && (defined (__linux__) || defined (__APPLE__))
#  define KSJSCZ_IMPORT_EXPORT __attribute__((visibility("default")))
#  if defined (__i386__)
#    define KSJSCZ_CALLTYPE __attribute__((stdcall))
#  else
#    define KSJSCZ_CALLTYPE /* default */
#  endif
#  ifndef EXTERN_C
#    define EXTERN_C extern "C"
#  endif

#else
#  error Unknown platform, file needs adaption
#endif


#define KSJSCZ_API KSJSCZ_IMPORT_EXPORT int KSJSCZ_CALLTYPE

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HANDLE
	typedef void* HANDLE;
#endif

enum KSJSCZ_DEVICE_TYPE
{
	KSJSCZ15_GE_X1200C = 0,
	KSJSCZ15_GE_E130M,
	KSJSCZ_DT_UNKNOWN  = -1,
};

enum KSJSCZ_SENSOR_TYPE
{
	KSJSCZ_ST_X1200C  = 0,
	KSJSCZ_ST_E130M,
	KSJSCZ_ST_UNKNOWN = -1
};

enum KSJ_ADDRESSMODE 
{ 
	KSJ_SKIPNONE = 0, 
	KSJ_SKIP2, 
	KSJ_SKIP3, 
	KSJ_SKIP4,
	KSJ_SKIP8 
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KSJSCZAPI函数返回代码
enum KSJSCZ_ERROR_LIST
{
	KSJSCZ_ERR_SUCCESS             = 0,
	KSJSCZ_ERR_ERROR               = -1001,
	KSJSCZ_ERR_NOT_INITIALIZED     = -1002,
	KSJSCZ_ERR_NOT_IMPLEMENTED     = -1003,
	KSJSCZ_ERR_RESOURCE_IN_USE     = -1004,
	KSJSCZ_ERR_ACCESS_DENIED       = -1005,
	KSJSCZ_ERR_INVALID_HANDLE      = -1006,
	KSJSCZ_ERR_INVALID_ID          = -1007,
	KSJSCZ_ERR_NO_DATA             = -1008,
	KSJSCZ_ERR_INVALID_PARAMETER   = -1009,
	KSJSCZ_ERR_IO                  = -1010,
	KSJSCZ_ERR_TIMEOUT             = -1011,
	KSJSCZ_ERR_ABORT               = -1012,
	KSJSCZ_ERR_INVALID_BUFFER      = -1013, 
	KSJSCZ_ERR_NOT_AVAILABLE       = -1014, 
	KSJSCZ_ERR_INVALID_ADDRESS     = -1015, 
	KSJSCZ_ERR_BUFFER_TOO_SMALL    = -1016, 
	KSJSCZ_ERR_INVALID_INDEX       = -1017, 
	KSJSCZ_ERR_PARSING_CHUNK_DATA  = -1018, 
	KSJSCZ_ERR_INVALID_VALUE       = -1019,
	KSJSCZ_ERR_RESOURCE_EXHAUSTED  = -1020, 
	KSJSCZ_ERR_OUT_OF_MEMORY       = -1021,
	KSJSCZ_ERR_BUSY                = -1022,
	KSJSCZ_ERR_PL_FAIL             = -1023,
	KSJSCZ_ERR_BUS_INVALID         = -1024,
	KSJSCZ_ERR_SENSOR_INVALID      = -1025,
	KSJSCZ_ERR_PL_INVALID          = -1026,

	KSJSCZ_ERR_CUSTOM_ID           = -10000
};

typedef void(*KSJSCZ_TRIGGER_CALLBACK)(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KSJSCZAPI接口函数
KSJSCZ_API KSJSCZ_Init();
KSJSCZ_API KSJSCZ_UnInit( );

KSJSCZ_API KSJSCZ_GetDeviceInformation( enum KSJSCZ_DEVICE_TYPE *pDeviceType, unsigned long *pulPLVersion);
KSJSCZ_API KSJSCZ_GetSensorNum( int *pnSensorNum );
KSJSCZ_API KSJSCZ_GetSensorType(int nSensorIndex, enum KSJSCZ_SENSOR_TYPE *pSensorType);
KSJSCZ_API KSJSCZ_GetCaptureFieldOfViewRange( int nSensorIndex, unsigned long *pulColSizeMin, unsigned long *pulRowSizeMin, unsigned long *pulColSizeMax, unsigned long *pulRowSizeMax);
KSJSCZ_API KSJSCZ_SetCaptureFieldOfView(int nSensorIndex, unsigned long ulColStart, unsigned long ulRowStart, unsigned long ulColSize, unsigned long ulRowSize);
KSJSCZ_API KSJSCZ_GetCaptureFieldOfView(int nSensorIndex, unsigned long *pulColStart, unsigned long *pulRowStart, unsigned long *pulColSize, unsigned long *pulRowSize);
KSJSCZ_API KSJSCZ_GetCaptureSize(int nSensorIndex, int *pnWidth, int *pnHeight, int *pnBitCount);
KSJSCZ_API KSJSCZ_CaptureData(int nSensorIndex, unsigned char **pDataBuffer);
KSJSCZ_API KSJSCZ_GetGainRange(int nSensorIndex, unsigned long *pulValueMin, unsigned long *pulValueMax);
KSJSCZ_API KSJSCZ_SetGain(int nSensorIndex, unsigned long ulValue);
KSJSCZ_API KSJSCZ_GetGain(int nSensorIndex, unsigned long *pulValue);
KSJSCZ_API KSJSCZ_GetExposureLinesRange(int nSensorIndex, unsigned long *pulExposureLinesMin, unsigned long *pulExposureLinesMax);
KSJSCZ_API KSJSCZ_SetExposureLines(int nSensorIndex, unsigned long ulExposureLines);
KSJSCZ_API KSJSCZ_GetExposureLines(int nSensorIndex, unsigned long *pulExposureLines);
KSJSCZ_API KSJSCZ_GetExposureTimeRange(int nSensorIndex, float *pfExposureTimeMin, float *pfExposureTimeMax);
KSJSCZ_API KSJSCZ_SetExposureTime(int nSensorIndex, float fExposureTime);
KSJSCZ_API KSJSCZ_GetExposureTime(int nSensorIndex, float *pfExposureTime);
KSJSCZ_API KSJSCZ_ReleaseBuffer(int nSensorIndex);
// Enable or Disable Log output
KSJSCZ_API  KSJSCZ_LogSet(bool bEnable, const char *pszFolder);
// Get Log Status
KSJSCZ_API  KSJSCZ_LogGet(bool *pbEnable, char *pszFolder);
// Get KSJSCZApi Version, call any time.
KSJSCZ_API  KSJSCZ_GetLibVersion(int *pnMaj1, int *pnMaj2, int *pnMin1, int *pnMin2);
// let user set second of timeout
KSJSCZ_API KSJSCZ_CaptureSetTimeOut(int nSensorIndex, unsigned long ulTimeOut); // unit is second
KSJSCZ_API  KSJSCZ_TriggerCallbackSet(int nSensorIndex, KSJSCZ_TRIGGER_CALLBACK pfTriggerCallback, void *lpContext);
KSJSCZ_API  KSJSCZ_HelperSaveToBmp( unsigned char *pData, int nWidth, int nHeight, int nBitCount, const char *pszFileName );
KSJSCZ_API KSJSCZ_SetAddressMode(int nSensorIndex, enum KSJ_ADDRESSMODE AddressMode);
KSJSCZ_API KSJSCZ_GetAddressMode(int nSensorIndex, enum KSJ_ADDRESSMODE *pAddressMode);

#ifdef __cplusplus
}
#endif

#endif
