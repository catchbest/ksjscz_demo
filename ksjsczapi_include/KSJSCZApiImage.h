#ifndef _KSJAPI_IMAGE_H__
#define _KSJAPI_IMAGE_H__

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


	KSJSCZ_API  KSJ_SetContrast(int nSensorIndex, bool bMonochrome, int nContrast);

	//以下接口有一些问题，FPGA的Monochrome接口读取没有开放
	//KSJSCZ_API  KSJ_SetMonochrome(int nSensorIndex, bool bMonochrome);
	//KSJSCZ_API  KSJ_GetMonochrome(int nSensorIndex, bool* pbMonochrome);

	// Same to Parameter KSJ_CONTRAST（-128~128）， Software Preccess, may influence capture efficiency or preivew frame rate.
	//KSJSCZ_API  KSJ_ProcessContrastGetRange(int nSensorIndex, int *pnMinContrast, int *pnMaxContrast);
	//KSJSCZ_API  KSJ_ProcessContrastSet(int nSensorIndex, int nContrast);
	//KSJSCZ_API  KSJ_ProcessContrastGet(int nSensorIndex, int *pnContrast);

	KSJSCZ_API  KSJ_AutoWhiteBlance(int nSensorIndex, KSJ_AWB_TYPE WbPresetting);
	KSJSCZ_API  KSJ_SetSharpness(int nSensorIndex, KSJ_SHARPNESS_TYPE SharpnessType);

	// 设置Gamma值，范围 -9 - +9
	KSJSCZ_API  KSJ_GammaGetRange(int nSensorIndex, int *pnMinGamma, int *pnMaxGamm);
	KSJSCZ_API  KSJ_GammaSetValue(int nSensorIndex, int nValue);
	KSJSCZ_API  KSJ_GammaGetValue(int nSensorIndex, int *pnValue);

	// For 4k
	KSJSCZ_API  KSJ_FreezeImage(int nSensorIndex, bool bFreeze);
	KSJSCZ_API  KSJ_ImageIsFreeze(int nSensorIndex, bool* pbFreezed);

	KSJSCZ_API  KSJ_CaptureImage(int nSensorIndex, unsigned int nTimeoutMS);
	KSJSCZ_API  KSJ_ReviewImage(int nSensorIndex, unsigned char* pImageBuffer, int nWidth, int nHeight, int nBitCount);

#ifdef __cplusplus
}
#endif

#endif