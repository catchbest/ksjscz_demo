#ifndef __KSJ_SCZ_API_IO_H__
#define __KSJ_SCZ_API_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

// ��ȡ�豸֧�ּ�·io���á�
KSJSCZ_API  KSJSCZ_GpioGetNum( unsigned short *pusGpioNum );

// ����GPIO���ŵ��������״̬��usDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJSCZ_API  KSJSCZ_GpioSetDirection( unsigned short usDirection);
// ��ȡGPIO���ŵ��������״̬��pusDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJSCZ_API  KSJSCZ_GpioGetDirection( unsigned short *pusDirection);

// ����GPIO���������ֻ��usDirection��Ӧλ����Ϊ1�����Ų���ͨ���˺����������������usGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJSCZ_API  KSJSCZ_GpioSetStatus(unsigned short usGpioStatus);
// ��ȡGPIO����״̬��*pusGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJSCZ_API  KSJSCZ_GpioGetStatus(unsigned short *pusGpioStatus);

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
