#ifndef __KSJ_SCZ_API_TRIGGER_H__
#define __KSJ_SCZ_API_TRIGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

// Empty All Frame Buffers. 
KSJSCZ_API  KSJSCZ_EmptyFrameBuffer(int nSensorIndex);

// Trigger Mode
enum KSJSCZ_TRIGGER_MODE
{
	KSJSCZ_TM_CMD_CONTINUE,
	KSJSCZ_TM_CMD_SINGLE,
	KSJSCZ_TM_EXT_LEVEL_HI,
	KSJSCZ_TM_EXT_LEVEL_LO,
	KSJSCZ_TM_EXT_EDGE_POS,
	KSJSCZ_TM_EXT_EDGE_NEG,
};

// Set Trigger Mode
KSJSCZ_API  KSJSCZ_TriggerModeSet(int nSensorIndex, unsigned long TriggerMode, bool bCreate);// bCreate: 1(自动创建线程); 0(用户自行创建线程)
KSJSCZ_API  KSJSCZ_TriggerModeGet(int nSensorIndex, unsigned long *pTriggerMode);


KSJSCZ_API  KSJSCZ_TriggerDelayGetRange(int nSensorIndex, unsigned long *pwMin, unsigned long *pwMax);
KSJSCZ_API  KSJSCZ_TriggerDelaySet(int nSensorIndex, unsigned long ulDelay);
KSJSCZ_API  KSJSCZ_TriggerDelayGet(int nSensorIndex, unsigned long *pulDelay);

enum KSJSCZ_FRAME_BUF
{
	KSJSCZ_FBUF_COUNT4,
	KSJSCZ_FBUF_COUNT1,
	KSJSCZ_FBUF_COUNT2,
	KSJSCZ_FBUF_COUNT3,
};

KSJSCZ_API  KSJSCZ_GetFrameBufNum(unsigned long *pulNumber);
KSJSCZ_API  KSJSCZ_SetFrameBufNum(unsigned long ulNumber);
KSJSCZ_API  KSJSCZ_GetMultiFrame(unsigned long *pulValue);
KSJSCZ_API  KSJSCZ_SetMultiFrame(unsigned long ulValue);
KSJSCZ_API  KSJSCZ_GetMultiFrameRange(unsigned long *pulMin,unsigned long *pulMax);
KSJSCZ_API  KSJSCZ_GetFixFrameRate(unsigned long *pulRate);
KSJSCZ_API  KSJSCZ_SetFixFrameRate(unsigned long ulRate);
KSJSCZ_API  KSJSCZ_GetTriggerFilter(unsigned short *pwFilter); // 配置过滤外触发信号噪声的时间参数
KSJSCZ_API  KSJSCZ_SetTriggerFilter(unsigned short wFilter);
KSJSCZ_API  KSJSCZ_GetTriggerFilterRange (unsigned short *pwMin,unsigned short *pwMax);

#ifdef __cplusplus
}
#endif

#endif

