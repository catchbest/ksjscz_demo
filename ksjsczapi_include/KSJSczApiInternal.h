#ifndef __KSJ_SCZ_API_INTERNAL_H___
#define __KSJ_SCZ_API_INTERNAL_H___

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


#define KSJSCZ_API KSJSCZ_IMPORT_EXPORT int KSJSCZ_CALLTYPE


#ifdef __cplusplus
extern "C" {
#endif

#include "KSJSczApiDataType.h"


// Internal
	KSJSCZ_API KSJSCZ_RdRegFPGA(int nSensorIndex, unsigned short usRegAddress, unsigned int *pulRegValue);
	KSJSCZ_API KSJSCZ_WrRegFPGA(int nSensorIndex, unsigned short usRegAddress, unsigned int ulRegValue);

	KSJSCZ_API KSJSCZ_RdSensorReg(int nSensorIndex, unsigned short usRegAddress, unsigned int *pulRegValue);
	KSJSCZ_API KSJSCZ_WrSensorReg(int nSensorIndex, unsigned short usRegAddress, unsigned int ulRegValue);


#ifdef __cplusplus
}
#endif

#endif
