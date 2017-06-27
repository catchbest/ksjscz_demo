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
KSJSCZ_API  KSJSCZ_GpioGetNum( unsigned short *pusGpioNum );

// id0/1/2 input  id3/4/5/6/7/8/9 output
KSJSCZ_API  KSJSCZ_GpioSet(int id, bool bValue);
KSJSCZ_API  KSJSCZ_GpioGet(int id, bool* pbValue);

//////////////////////////////////////////////////////////////
//   ����4���ӿ��Ѿ�������ԭ��bit0/1 input; bit2/3/4/5/6/7 output�Ѿ�����Ϊ 3bit input��7bit output
// ����GPIO���ŵ��������״̬��usDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJSCZ_API  KSJSCZ_GpioSetDirection( unsigned short usDirection);
// ��ȡGPIO���ŵ��������״̬��pusDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJSCZ_API  KSJSCZ_GpioGetDirection( unsigned short *pusDirection);

// ����GPIO���������ֻ��usDirection��Ӧλ����Ϊ1�����Ų���ͨ���˺����������������usGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJSCZ_API  KSJSCZ_GpioSetStatus(unsigned short usGpioStatus);
// ��ȡGPIO����״̬��*pusGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJSCZ_API  KSJSCZ_GpioGetStatus(unsigned short *pusGpioStatus);
////////////////////////////////////////////////////////////////

// ����ƿ���
KSJSCZ_API  KSJSCZ_FlashSetEnable(int nSensorIndex, bool bEnable);
KSJSCZ_API  KSJSCZ_FlashGetEnable(int nSensorIndex, bool *pbEnable);

// ����ת - �ߵ�ƽ��Ч����ת - �͵�ƽ��Ч
KSJSCZ_API  KSJSCZ_FlashSetInvert(int nSensorIndex, bool bEnable);
KSJSCZ_API  KSJSCZ_FlashGetInvert(int nSensorIndex, bool *pbEnable);

#ifdef __cplusplus
}
#endif

#endif
