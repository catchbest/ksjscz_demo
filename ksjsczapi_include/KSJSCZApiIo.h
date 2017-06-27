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

// 获取设备支持几路io设置。
KSJSCZ_API  KSJSCZ_GpioGetNum( unsigned short *pusGpioNum );

// id0/1/2 input  id3/4/5/6/7/8/9 output
KSJSCZ_API  KSJSCZ_GpioSet(int id, bool bValue);
KSJSCZ_API  KSJSCZ_GpioGet(int id, bool* pbValue);

//////////////////////////////////////////////////////////////
//   下面4个接口已经废弃，原来bit0/1 input; bit2/3/4/5/6/7 output已经升级为 3bit input，7bit output
// 设置GPIO引脚的输入输出状态，usDirection位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出，=0表示此GPIO输入)
KSJSCZ_API  KSJSCZ_GpioSetDirection( unsigned short usDirection);
// 获取GPIO引脚的输入输出状态，pusDirection位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出，=0表示此GPIO输入)
KSJSCZ_API  KSJSCZ_GpioGetDirection( unsigned short *pusDirection);

// 控制GPIO引脚输出，只有usDirection相应位设置为1的引脚才能通过此函数控制引脚输出。usGpioStatus位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出TTL高电平，=0表示此GPIO输出TTL低电平)
KSJSCZ_API  KSJSCZ_GpioSetStatus(unsigned short usGpioStatus);
// 读取GPIO引脚状态，*pusGpioStatus位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出TTL高电平，=0表示此GPIO输出TTL低电平)
KSJSCZ_API  KSJSCZ_GpioGetStatus(unsigned short *pusGpioStatus);
////////////////////////////////////////////////////////////////

// 闪光灯控制
KSJSCZ_API  KSJSCZ_FlashSetEnable(int nSensorIndex, bool bEnable);
KSJSCZ_API  KSJSCZ_FlashGetEnable(int nSensorIndex, bool *pbEnable);

// 不翻转 - 高电平有效，翻转 - 低电平有效
KSJSCZ_API  KSJSCZ_FlashSetInvert(int nSensorIndex, bool bEnable);
KSJSCZ_API  KSJSCZ_FlashGetInvert(int nSensorIndex, bool *pbEnable);

#ifdef __cplusplus
}
#endif

#endif
