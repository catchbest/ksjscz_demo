#ifndef _KSJSCZAPI_CODE_H__
#define _KSJSCZAPI_CODE_H__

// KSJSCZAPI函数返回代码
enum KSJSCZ_ERROR_LIST
{
	KSJSCZ_ERR_SUCCESS              = 0,
	KSJSCZ_ERR_ERROR                = -1001,
	KSJSCZ_ERR_NOT_INITIALIZED      = -1002,
	KSJSCZ_ERR_NOT_IMPLEMENTED      = -1003,
	KSJSCZ_ERR_RESOURCE_IN_USE      = -1004,
	KSJSCZ_ERR_ACCESS_DENIED        = -1005,
	KSJSCZ_ERR_INVALID_HANDLE       = -1006,
	KSJSCZ_ERR_INVALID_ID           = -1007,
	KSJSCZ_ERR_NO_DATA              = -1008,
	KSJSCZ_ERR_INVALID_PARAMETER    = -1009,
	KSJSCZ_ERR_IO                   = -1010,
	KSJSCZ_ERR_TIMEOUT              = -1011,
	KSJSCZ_ERR_ABORT                = -1012,
	KSJSCZ_ERR_INVALID_BUFFER       = -1013,
	KSJSCZ_ERR_NOT_AVAILABLE        = -1014,
	KSJSCZ_ERR_INVALID_ADDRESS      = -1015,
	KSJSCZ_ERR_BUFFER_TOO_SMALL     = -1016,
	KSJSCZ_ERR_INVALID_INDEX        = -1017,
	KSJSCZ_ERR_PARSING_CHUNK_DATA   = -1018,
	KSJSCZ_ERR_INVALID_VALUE        = -1019,
	KSJSCZ_ERR_RESOURCE_EXHAUSTED   = -1020,
	KSJSCZ_ERR_OUT_OF_MEMORY        = -1021,
	KSJSCZ_ERR_BUSY                 = -1022,
	KSJSCZ_ERR_PL_FAIL              = -1023,
	KSJSCZ_ERR_BUS_INVALID          = -1024,
	KSJSCZ_ERR_SENSOR_INVALID       = -1025,
	KSJSCZ_ERR_PL_INVALID           = -1026,
	KSJSCZ_ERR_CAPTURESTOP          = -1027,

	KSJSCZ_ERR_CUSTOM_ID            = -10000
};

#define		RET_SUCCESS			     0     // Function Return Successfully.
#define		RET_PARAMERROR			-1     // User's Parameter Passed to API Error.
#define		RET_MALLOCFAIL			-2     // Memory Allocated Fail.
#define		RET_NOTSUPPORT			-3     // Function not supported by such type camera.
#define		RET_DEVICENOTEXIST		-4     // Device doesn't be detected.
#define		RET_DEVICENOTINIT		-5     // Device haven't be initialized
#define		RET_VIOLATION			-6     // This operation is conflict to other operation.
#define		RET_NOPRIVILEGE			-7     // User no privilege
#define		RET_FAIL			    -8     // Function Return Failed.( Normal Error, no Detail )
#define		RET_WRONG			    -9     // Same to RET_FAIL.
#define     RET_RECOVERY_SUCCESS    -10    // Device is recovered successfully.
#define     RET_RECOVERY_FAIL       -11    // Device recovered, but fail.
#define     RET_BADFRAME            -12    // Bad Frame comes from sensor, should be skipped. 
#define     RET_INVALIDFRAME        -13    // Invalid Frame, Transmission Error, this frame should re-get.
#define     RET_ZEROFRAME           -14    // 帧存相机会返回此值，表示采集图像数据0字节，错误的帧
#define     RET_VERSION_ERROR       -15    // 版本错误
#define     RET_TIMEOUT             -16    // 当设置读取超时之后不进行恢复时，采集函数会返回此数值，而不会返回恢复的状态
#define     RET_DEVICECLOSED        -17
#define     RET_BUSNOTINIT          -18    // 总线没有初始化
#define     RET_CAM_NOT_CREATED     -19
#define     RET_INVALID_HANDLE      -20

#endif