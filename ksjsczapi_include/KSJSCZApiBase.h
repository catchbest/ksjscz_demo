#ifndef __KSJ_SCZ_API_H___
#define __KSJ_SCZ_API_H___

#if defined (_WIN32)
#  ifdef KSJSCZAPI_EXPORTS
#    define KSJSCZ_IMPORT_EXPORT __declspec(dllexport)
#  else
#    define KSJSCZ_IMPORT_EXPORT __declspec(dllimport)
#  endif
#  if defined (_M_IX86) || defined (__i386__)
#    define KSJSCZ_CALLTYPE __stdcall
#  else
#    define KSJSCZ_CALLTYPE  
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


#ifndef _WIN32
#define KSJSCZ_API int
#else
#define KSJSCZ_API KSJSCZ_IMPORT_EXPORT int KSJSCZ_CALLTYPE
#endif


#ifdef __cplusplus
extern "C" {
#endif

#include "KSJSczApiDataType.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enable or Disable Log output
//KSJSCZ_API  KSJSCZ_LogSet(bool bEnable, const char *pszFolder);
// Get Log Status
//KSJSCZ_API  KSJSCZ_LogGet(bool *pbEnable, char *pszFolder);

// Get KSJSCZApi Version, call any time.
KSJSCZ_API  KSJSCZ_GetLibVersion(int *pnMaj1, int *pnMaj2, int *pnMin1, int *pnMin2);

// KSJSCZAPI½Ó¿Úº¯Êý
KSJSCZ_API KSJSCZ_Init();
KSJSCZ_API KSJSCZ_UnInit( );

KSJSCZ_API KSJSCZ_GetSensorNum( int *pnSensorNum );
KSJSCZ_API KSJSCZ_GetSensorType(int nSensorIndex, enum KSJSCZ_SENSOR_TYPE *pSensorType);
KSJSCZ_API KSJSCZ_GetDeviceInformation(int nSensorIndex, enum KSJSCZ_DEVICE_TYPE *pDeviceType, unsigned long *pulPLVersion);

KSJSCZ_API KSJSCZ_GetCaptureFieldOfViewRange( int nSensorIndex, unsigned long *pulColSizeMin, unsigned long *pulRowSizeMin, unsigned long *pulColSizeMax, unsigned long *pulRowSizeMax);
KSJSCZ_API KSJSCZ_SetCaptureFieldOfView(int nSensorIndex, unsigned long ulColStart, unsigned long ulRowStart, unsigned long ulColSize, unsigned long ulRowSize);
KSJSCZ_API KSJSCZ_GetCaptureFieldOfView(int nSensorIndex, unsigned long *pulColStart, unsigned long *pulRowStart, unsigned long *pulColSize, unsigned long *pulRowSize);
KSJSCZ_API KSJSCZ_SetAddressMode(int nSensorIndex, KSJ_ADDRESSMODE AddressMode);
KSJSCZ_API KSJSCZ_GetAddressMode(int nSensorIndex, KSJ_ADDRESSMODE *pAddressMode);
KSJSCZ_API KSJSCZ_GetCaptureSize(int nSensorIndex, int *pnWidth, int *pnHeight, int *pnBitCount);
KSJSCZ_API KSJSCZ_CaptureSetTimeOut(int nSensorIndex, unsigned long ulTimeOut); // unit is second
KSJSCZ_API KSJSCZ_CaptureData(int nSensorIndex, unsigned char **pDataBuffer);
KSJSCZ_API KSJSCZ_ReleaseBuffer(int nSensorIndex);

KSJSCZ_API KSJSCZ_GetGainRange(int nSensorIndex, unsigned long *pulValueMin, unsigned long *pulValueMax);
KSJSCZ_API KSJSCZ_SetGain(int nSensorIndex, unsigned long ulValue);
KSJSCZ_API KSJSCZ_GetGain(int nSensorIndex, unsigned long *pulValue);
KSJSCZ_API KSJSCZ_GetExposureLinesRange(int nSensorIndex, unsigned long *pulExposureLinesMin, unsigned long *pulExposureLinesMax);
KSJSCZ_API KSJSCZ_SetExposureLines(int nSensorIndex, unsigned long ulExposureLines);
KSJSCZ_API KSJSCZ_GetExposureLines(int nSensorIndex, unsigned long *pulExposureLines);
KSJSCZ_API KSJSCZ_GetExposureTimeRange(int nSensorIndex, float *pfExposureTimeMin, float *pfExposureTimeMax);
KSJSCZ_API KSJSCZ_SetExposureTime(int nSensorIndex, float fExposureTime);
KSJSCZ_API KSJSCZ_GetExposureTime(int nSensorIndex, float *pfExposureTime);

KSJSCZ_API KSJSCZ_SetMirror(int nSensorIndex, bool bMirror);
KSJSCZ_API KSJSCZ_GetMirror(int nSensorIndex, bool *pbMirror);
KSJSCZ_API KSJSCZ_SetFlip(int nSensorIndex, bool bFlip);
KSJSCZ_API KSJSCZ_GetFlip(int nSensorIndex, bool *pbFlip);

KSJSCZ_API KSJSCZ_HelperSaveToBmp( unsigned char *pData, int nWidth, int nHeight, int nBitCount, const char *pszFileName );

KSJSCZ_API  KSJSCZ_LogSet(bool bEnable, const char *pszFolder);
KSJSCZ_API  KSJSCZ_LogGet(bool *pbEnable, char *pszFolder);



#ifdef __cplusplus
}
#endif

#endif
