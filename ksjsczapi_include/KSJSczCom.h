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
#define KSJCOM_RET_OPENED     -3    // 表示端口已经打开，不能重复打开


// 初始化KSJCom动态库
	KSJSCZ_API  KSJCOM_Init(void);

// 反初始化KSJCom动态库
	KSJSCZ_API  KSJCOM_UnInit(void);

// 得到COM端口数目
	KSJSCZ_API  KSJCOM_GetCount(int* pnCount);

// 打开相应的COM口
// nStopBits 0 - 1 stop bit; 1 - 1.5 stop bits; 2 - 2 stop bits
	KSJSCZ_API  KSJCOM_Open(int nChannel, int nBaud = 4800, unsigned char nByteSize = 8, unsigned char nStopBits = 0);

// 发送nBytesNum个字节的数据，pbtData由调用者分配并负责释放
// 返回成功发送的字节数
	KSJSCZ_API  KSJCOM_SendData(int nChannel, unsigned char *pbtData, int nBytesNum);


// nBytesNum为要读取的字节个数，如果nBytesNum小于实际发送过来的字节个数，则按照nBytesNum读取，否则按照实际发送过来的字节个数读取
// 返回实际读取到的字节个数，pbtData由调用者分配并负责释放
	KSJSCZ_API  KSJCOM_ReadData(int nChannel, unsigned char *pbtData, int nBytesNum, int& nBytesRead);

// 关闭相应的COM口
	KSJSCZ_API  KSJCOM_Close(int nChannel);


#ifdef __cplusplus
}
#endif

#endif

