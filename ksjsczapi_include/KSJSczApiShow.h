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
	* ָ����ʾͼ���label �ĳߴ�
	* (unXoffset,unYoffset) ����ʾ���ھ���ʾ�����Ͻǵ�ƫ��
	*/
	KSJSCZ_API KSJSCZ_SetVideoWidgetPos(int nSensorIndex, unsigned int unXoffset, unsigned int unYoffset, unsigned int unWidgetWidth, unsigned int unWidgetHeight);

	/*
	* ָ��ͼ�����ʾ�ߴ�
	* (nXoffset,nYoffset) ��ͼ�����ʾ��ʾ����VideoWidget���Ͻǵ�ƫ��
	*/
	KSJSCZ_API KSJSCZ_SetPosition(int nSensorIndex, int nXoffset, int nYoffset, unsigned int unDisplayWidth, unsigned int unDisplayHeight);

	/*
	* ��ʾһ֡ͼ�񣬴�ͼ��Ϊ��Sensor�ɼ���FrameBuffer�ĵ�ǰ֡
	*/
	KSJSCZ_API KSJSCZ_ShowCaptureData(int nSensorIndex, unsigned char *pDataBuffer);

	// ��Ҫ��ʾʱ���ɹ̶������ڴ�������ڴ�
	KSJSCZ_API KSJSCZ_Malloc(unsigned int unBufferSize, unsigned char **ppDataBuffer);

	// �ͷ������ڴ���е�һ���ڴ�
	KSJSCZ_API KSJSCZ_Free(unsigned char **ppDataBuffer);

	// ��ʾһ֡ͼ�񣬴�ͼ��Ϊ�û����ص�DataBuffer (�� KSJSCZ_Malloc ����)�е�ͼ������
	KSJSCZ_API KSJSCZ_ShowUserLoadData(int nSensorIndex, unsigned char *pDataBuffer, unsigned int unRawWidth, unsigned int unRawHeight, unsigned int unBitCount);

#ifdef __cplusplus
}
#endif

#endif
