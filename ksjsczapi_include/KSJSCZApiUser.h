#ifndef __KSJ_SCZ_API_USER_H___
#define __KSJ_SCZ_API_USER_H___

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

#include "../../../101/git.KSJSczApi/KSJSczApi.Inc/KSJSczApiDataType.h"

// 读写用户的寄存器
// 只能操作0x94的bit[16:23]，0xB4，0xB8，0xBC，0xC0，0xC4，0xC8，0xCC，0xD0，0xD4的FPGA寄存器
KSJSCZ_API KSJSCZ_RdUserRegFPGA(unsigned short usRegAddress, unsigned int *pulRegValue);
KSJSCZ_API KSJSCZ_WrUserRegFPGA(unsigned short usRegAddress, unsigned int ulRegValue);

KSJSCZ_API KSJSCZ_RdRegUserVDMA(int nVdmaIndex, unsigned short usRegAddress, unsigned int *pulRegValue);
KSJSCZ_API KSJSCZ_WrRegUserVDMA(int nVdmaIndex, unsigned short usRegAddress, unsigned int ulRegValue);

KSJSCZ_API KSJSCZ_WrRegUserVDMADataAddr(int nVdmaIndex, unsigned short usRegAddress, unsigned char* pUseDataBuffer);   // will flush user data

KSJSCZ_API KSJSCZ_FlushUserData(unsigned char* pUseDataBuffer, unsigned int len);
KSJSCZ_API KSJSCZ_WrtieDataAddrToVDMAReg(int nVdmaIndex, unsigned short usRegAddress, unsigned char* pUseDataBuffer);                     // will not flush user data
KSJSCZ_API KSJSCZ_WrtieFrameAddrToVDMAReg(int nVdmaIndex, unsigned short usRegAddress, int nSensorIndex, unsigned char* pFrameBuffer);    // will not flush frame data

#ifdef __cplusplus
}
#endif

#endif
