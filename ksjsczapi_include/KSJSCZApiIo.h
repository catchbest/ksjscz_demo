#ifndef __KSJ_SCZ_API_IO_H__
#define __KSJ_SCZ_API_IO_H__

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

// ��ȡ�豸֧�ּ�·io���á�
KSJSCZ_API  KSJSCZ_GpioGetNum(unsigned short *pusGpioInNum, unsigned short *pusGpioOutNum);

// id0/1/2 input  id3/4/5/6/7/8/9 output
KSJSCZ_API  KSJSCZ_GpioSet(int id, bool bValue);
KSJSCZ_API  KSJSCZ_GpioGet(int id, bool* pbValue);


// ����ƿ���
KSJSCZ_API  KSJSCZ_FlashSetEnable(int nSensorIndex, bool bEnable);
KSJSCZ_API  KSJSCZ_FlashGetEnable(int nSensorIndex, bool *pbEnable);

// ����ת - �ߵ�ƽ��Ч����ת - �͵�ƽ��Ч
KSJSCZ_API  KSJSCZ_FlashSetInvert(int nSensorIndex, bool bEnable);
KSJSCZ_API  KSJSCZ_FlashGetInvert(int nSensorIndex, bool *pbEnable);

// �������
KSJSCZ_API KSJSCZ_SetMotorMoveStepNumber(int nSensorIndex, unsigned short usStep);     // ���ü���ִ�еĲ�����usStep���ֵ��Ҫ����3000
KSJSCZ_API KSJSCZ_GetMotorMoveStepNumber(int nSensorIndex, unsigned short *pusStep);    // ȡ���Ѿ�ִ�еĲ���
KSJSCZ_API KSJSCZ_MotorControlExecute(int nSensorIndex, bool bRun, bool bForward, unsigned int ulSpeed);        // ִ�в�����bRun=1ִ�иղ����õĲ�����bRun=0������Ѿ�ִ�еĲ�����ulSpeed��Ҫ����100Hz��
KSJSCZ_API KSJSCZ_MotorExecute(int nSensorIndex, unsigned short usStep, bool bForward, unsigned int ulSpeed, unsigned int nTimeOutMS);   // ���Ƶ��ִ����usStep

// ����ƿ���
KSJSCZ_API KSJSCZ_SetFlashEnbale(int nSensorIndex, bool bEnable, unsigned int unFlashRate);     // �����ʹ��


#ifdef __cplusplus
}
#endif

#endif
