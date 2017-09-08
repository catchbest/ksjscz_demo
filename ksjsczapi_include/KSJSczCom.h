#ifndef _KSJSCZ_COM_H__
#define _KSJSCZ_COM_H__

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

#define KSJCOM_RET_SUCCESS    0
#define KSJCOM_RET_FAIL       -1
#define KSJCOM_RET_DLLNOTINIT -2
#define KSJCOM_RET_OPENED     -3    // ��ʾ�˿��Ѿ��򿪣������ظ���


// ��ʼ��KSJCom��̬��
	KSJSCZ_API  KSJCOM_Init(void);

// ����ʼ��KSJCom��̬��
	KSJSCZ_API  KSJCOM_UnInit(void);

// �õ�COM�˿���Ŀ
	KSJSCZ_API  KSJCOM_GetCount(int* pnCount);

// ����Ӧ��COM��
// nStopBits 0 - 1 stop bit; 1 - 1.5 stop bits; 2 - 2 stop bits
	KSJSCZ_API  KSJCOM_Open(int nChannel, int nBaud = 4800, unsigned char nByteSize = 8, unsigned char nStopBits = 0);

// ����nBytesNum���ֽڵ����ݣ�pbtData�ɵ����߷��䲢�����ͷ�
// ���سɹ����͵��ֽ���
	KSJSCZ_API  KSJCOM_SendData(int nChannel, unsigned char *pbtData, int nBytesNum);


// nBytesNumΪҪ��ȡ���ֽڸ��������nBytesNumС��ʵ�ʷ��͹������ֽڸ���������nBytesNum��ȡ��������ʵ�ʷ��͹������ֽڸ�����ȡ
// ����ʵ�ʶ�ȡ�����ֽڸ�����pbtData�ɵ����߷��䲢�����ͷ�
	KSJSCZ_API  KSJCOM_ReadData(int nChannel, unsigned char *pbtData, int nBytesNum, int& nBytesRead);

// �ر���Ӧ��COM��
	KSJSCZ_API  KSJCOM_Close(int nChannel);


#ifdef __cplusplus
}
#endif

#endif

