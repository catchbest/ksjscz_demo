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


KSJSCZ_API  KSJSCZ_GetCaptureStart(int nSensorIndex, bool *pbStart);
KSJSCZ_API  KSJSCZ_SetCaptureStart(int nSensorIndex, bool bStart);

// ���ô���ģʽ
enum KSJSCZ_TRIGGER_MODE
{
	KSJSCZ_TM_CMD_CONTINUE,
	KSJSCZ_TM_CMD_SINGLE,
	KSJSCZ_TRIMODE_EXTERNAL
};
KSJSCZ_API  KSJSCZ_SetTriggerMode(int nSensorIndex, enum KSJSCZ_TRIGGER_MODE  TriggerMode);
KSJSCZ_API  KSJSCZ_GetTriggerMode(int nSensorIndex, enum KSJSCZ_TRIGGER_MODE *pTriggerMode);

// ���ô����źŷ�ʽ����MODEΪKSJSCZ_TRIMODE_EXTERNAL��ʱ��������
enum KSJSCZ_TRIGGERMETHOD
{
	KSJSCZ_TRIMETHOD_FALLINGEDGE,
	KSJSCZ_TRIMETHOD_RISINGEDGE,
	KSJSCZ_TRIMETHOD_HIGHLEVEL,
	KSJSCZ_TRIMETHOD_LOWLEVEL
};
KSJSCZ_API  KSJSCZ_SetTriggerMethod(int nSensorIndex, enum KSJSCZ_TRIGGERMETHOD  TriggerMethod);
KSJSCZ_API  KSJSCZ_GetTriggerMethod(int nSensorIndex, enum KSJSCZ_TRIGGERMETHOD *pTriggerMethod);

// ���ÿ�ʼģʽ�������д���ģʽ������
enum KSJSCZ_STARTMODE
{
	KSJSCZ_STARTMODE_NONE,
	KSJSCZ_STARTMODE_REGISTER,
	KSJSCZ_STARTMODE_EXTERNAL
};
KSJSCZ_API  KSJSCZ_SetStartMode(int nSensorIndex, enum KSJSCZ_STARTMODE  StartMode);
KSJSCZ_API  KSJSCZ_GetStartMode(int nSensorIndex, enum KSJSCZ_STARTMODE *pStartMode);

// ���ý���ģʽ�������д���ģʽ������
enum KSJSCZ_STOPMODE
{
	KSJSCZ_STOPMODE_NONE,
	KSJSCZ_STOPMODE_REGISTER,
	KSJSCZ_STOPMODE_EXTERNAL,
	KSJSCZ_STOPMODE_MULTILINE
};
KSJSCZ_API  KSJSCZ_SetStopMode(int nSensorIndex, enum KSJSCZ_STOPMODE  StopMode);
KSJSCZ_API  KSJSCZ_GetStopMode(int nSensorIndex, enum KSJSCZ_STOPMODE *pStopMode);

// ������ʼ�����źŷ�ʽ������ʼ����ģʽΪ�ⲿ�ź�����
enum KSJSCZ_STARTMETHOD
{
	KSJSCZ_STARTMETHOD_FALLINGEDGE,
	KSJSCZ_STARTMETHOD_RISINGEDGE,
	KSJSCZ_STARTMETHOD_HIGHLEVEL,
	KSJSCZ_STARTMETHOD_LOWLEVEL
};
KSJSCZ_API  KSJSCZ_SetStartMethod(int nSensorIndex, enum KSJSCZ_STARTMETHOD  StartMethod);
KSJSCZ_API  KSJSCZ_GetStartMethod(int nSensorIndex, enum KSJSCZ_STARTMETHOD *pStartMethod);

// ������ʼ�����źŷ�ʽ������ʼ����ģʽΪ�ⲿ�ź�����
enum KSJSCZ_STOPMETHOD
{
	KSJSCZ_STOPMETHOD_FALLINGEDGE,
	KSJSCZ_STOPMETHOD_RISINGEDGE,
	KSJSCZ_STOPMETHOD_HIGHLEVEL,
	KSJSCZ_STOPMETHOD_LOWLEVEL
};
KSJSCZ_API  KSJSCZ_SetStopMethod(int nSensorIndex, enum KSJSCZ_STOPMETHOD  StopMethod);
KSJSCZ_API  KSJSCZ_GetStopMethod(int nSensorIndex, enum KSJSCZ_STOPMETHOD *pStopMethod);

// ���ù̶�֡��
KSJSCZ_API  KSJSCZ_GetFixFrameRate(int nSensorIndex, unsigned int *pulRate);
KSJSCZ_API  KSJSCZ_SetFixFrameRate(int nSensorIndex, unsigned int ulRate);

// �����ⴥ���ź��ӳ�
KSJSCZ_API  KSJSCZ_GetTriggerDelayRange(int nSensorIndex, unsigned int *pwMin, unsigned int *pwMax);
KSJSCZ_API  KSJSCZ_SetTriggerDelay(int nSensorIndex, unsigned int ulDelay);
KSJSCZ_API  KSJSCZ_GetTriggerDelay(int nSensorIndex, unsigned int *pulDelay);

// �����ⴥ���źŹ���
KSJSCZ_API  KSJSCZ_GetTriggerFilterRange(int nSensorIndex, unsigned short *pwMin, unsigned short *pwMax);
KSJSCZ_API  KSJSCZ_GetTriggerFilter(int nSensorIndex, unsigned short *pwFilter); // ���ù����ⴥ���ź�������ʱ�����
KSJSCZ_API  KSJSCZ_SetTriggerFilter(int nSensorIndex, unsigned short wFilter);

// �����ⴥ�����ڣ������ٸ��ⴥ���źţ������ɼ�һ֡ͼ��
KSJSCZ_API  KSJSCZ_GetTriggerSignalPeriod(int nSensorIndex, float* pfPeriodCount);
KSJSCZ_API  KSJSCZ_SetTriggerSignalPeriod(int nSensorIndex, float fPeriodCount);

// ������ʼ�����źŹ���
KSJSCZ_API  KSJSCZ_GetSESignalFilter(int nSensorIndex, unsigned int* puDelayUS);
KSJSCZ_API  KSJSCZ_SetWorkingSignalFilter(int nSensorIndex, unsigned int uDelayUS);

// ����ÿһ��Frame��֡��
KSJSCZ_API  KSJSCZ_GetMultiFrameRange(int nSensorIndex, unsigned int *pulMin, unsigned int *pulMax);
KSJSCZ_API  KSJSCZ_GetMultiFrame(int nSensorIndex, unsigned int *pulValue);
KSJSCZ_API  KSJSCZ_SetMultiFrame(int nSensorIndex, unsigned int ulValue);

// ����Frame����1-4
KSJSCZ_API  KSJSCZ_GetFrameBufNum(int nSensorIndex, unsigned int *pulNumber);
KSJSCZ_API  KSJSCZ_SetFrameBufNum(int nSensorIndex, unsigned int ulNumber);

// ����MultiLine��
KSJSCZ_API  KSJSCZ_GetMultiLineNum(int nSensorIndex, unsigned int *pulNumber);
KSJSCZ_API  KSJSCZ_SetMultiLineNum(int nSensorIndex, unsigned int ulNumber);

// ������ʼ�Ĵ���
KSJSCZ_API  KSJSCZ_SetWorkingRegister(int nSensorIndex, bool bStart);

#ifdef __cplusplus
}
#endif

#endif

