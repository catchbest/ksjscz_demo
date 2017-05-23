#ifndef __KSJ_SCZ_API_TRIGGER_H__
#define __KSJ_SCZ_API_TRIGGER_H__

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

// Empty All Frame Buffers. 
KSJSCZ_API  KSJSCZ_EmptyFrameBuffer(int nSensorIndex);

// Set Trigger Mode
KSJSCZ_API  KSJSCZ_SetTriggerMode(int nSensorIndex, enum KSJSCZ_TRIGGER_MODE TriggerMode);
KSJSCZ_API  KSJSCZ_GetTriggerMode(int nSensorIndex, enum KSJSCZ_TRIGGER_MODE *pTriggerMode);

KSJSCZ_API KSJSCZ_SetTriggerCallback(int nSensorIndex, KSJSCZ_TRIGGER_CALLBACK pfTriggerCallback);

KSJSCZ_API  KSJSCZ_GetTriggerDelayRange(int nSensorIndex, unsigned long *pwMin, unsigned long *pwMax);
KSJSCZ_API  KSJSCZ_SetTriggerDelay(int nSensorIndex, unsigned long ulDelay);
KSJSCZ_API  KSJSCZ_GetTriggerDelay(int nSensorIndex, unsigned long *pulDelay);

KSJSCZ_API  KSJSCZ_GetFixFrameRate(int nSensorIndex, unsigned long *pulRate);
KSJSCZ_API  KSJSCZ_SetFixFrameRate(int nSensorIndex, unsigned long ulRate);

KSJSCZ_API  KSJSCZ_GetMultiFrameRange(int nSensorIndex, unsigned long *pulMin, unsigned long *pulMax);
KSJSCZ_API  KSJSCZ_GetMultiFrame(int nSensorIndex, unsigned long *pulValue);
KSJSCZ_API  KSJSCZ_SetMultiFrame(int nSensorIndex, unsigned long ulValue);


KSJSCZ_API  KSJSCZ_GetTriggerFilterRange(int nSensorIndex, unsigned short *pwMin, unsigned short *pwMax);
KSJSCZ_API  KSJSCZ_GetTriggerFilter(int nSensorIndex, unsigned short *pwFilter); // 配置过滤外触发信号噪声的时间参数
KSJSCZ_API  KSJSCZ_SetTriggerFilter(int nSensorIndex, unsigned short wFilter);

//KSJSCZ_API  KSJSCZ_GetFrameBufNum(int nSensorIndex, unsigned long *pulNumber);
//KSJSCZ_API  KSJSCZ_SetFrameBufNum(int nSensorIndex, unsigned long ulNumber);


#ifdef __cplusplus
}
#endif

#endif

