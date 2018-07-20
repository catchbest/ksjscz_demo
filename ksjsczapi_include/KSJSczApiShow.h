#ifndef __KSJ_QT_API_H___
#define __KSJ_QT_API_H___

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

	/*
	* 指定显示图像的label 的尺寸
	* (unXoffset,unYoffset) 是显示窗口距显示器左上角的偏移
	*/
	KSJSCZ_API KSJSCZ_SetVideoWidgetPos(int nSensorIndex, unsigned int unXoffset, unsigned int unYoffset, unsigned int unWidgetWidth, unsigned int unWidgetHeight);

	/*
	* 指定图像的显示尺寸
	* (nXoffset,nYoffset) 是图像距显示显示窗口VideoWidget左上角的偏移
	*/
	KSJSCZ_API KSJSCZ_SetPosition(int nSensorIndex, int nXoffset, int nYoffset, unsigned int unDisplayWidth, unsigned int unDisplayHeight);

	/*
	* 显示一帧图像，此图像为从Sensor采集到FrameBuffer的当前帧
	*/
	KSJSCZ_API KSJSCZ_ShowCaptureData(int nSensorIndex, unsigned char *pDataBuffer);

	// 需要显示时，由固定物理内存池申请内存
	KSJSCZ_API KSJSCZ_Malloc(unsigned int unBufferSize, unsigned char **ppDataBuffer);

	// 释放物理内存池中的一块内存
	KSJSCZ_API KSJSCZ_Free(unsigned char **ppDataBuffer);

	// 显示一帧图像，此图像为用户加载到DataBuffer (由 KSJSCZ_Malloc 分配)中的图像数据
	KSJSCZ_API KSJSCZ_ShowUserLoadData(int nSensorIndex, unsigned char *pDataBuffer, unsigned int unRawWidth, unsigned int unRawHeight, unsigned int unBitCount);

#ifdef __cplusplus
}
#endif

#endif
