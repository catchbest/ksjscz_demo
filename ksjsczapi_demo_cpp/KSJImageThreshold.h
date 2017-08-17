/*
 * KSJImageThreshold.h
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */

#ifndef KSJIMAGETHRESHOLD_H_
#define KSJIMAGETHRESHOLD_H_


// ��ֵ��ͼ��
// nMode = 0ʱ�� >= nThreshold������Ϊ255�� < nThreshold������Ϊ0
// nMode = 1ʱ�� >= nThreshold������Ϊ0��   < nThreshold������Ϊ255
// ���ı�pData
int KSJIMAGE_Y8_ThresholdSingle(unsigned char *pData, int nWidth, int nHeight, int nThreshold, int nMode);
// ֻ���AOI���ж�ֵ��
int KSJIMAGE_Y8_ThresholdSingle_AOI(unsigned char *pData, int nWidth, int nHeight, int nThreshold, int nMode, int nAoiX, int nAoiY, int nAoiW, int nAoiH);


// nMode = 0ʱ�� >= nThresholdLow && <= nThresholdHig������Ϊ255������Ϊ0
// nMode = 1ʱ�� >= nThresholdLow && <= nThresholdHig������Ϊ0������Ϊ255
// ���ı�pData
int KSJIMAGE_Y8_ThresholdDouble(unsigned char *pData, int nWidth, int nHeight, int nThresholdLow, int nThresholdHig, int nMode);
int KSJIMAGE_Y8_ThresholdDouble_AOI(unsigned char *pData, int nWidth, int nHeight, int nThresholdLow, int nThresholdHig, int nMode, int nAoiX, int nAoiY, int nAoiW, int nAoiH);

#endif /* KSJIMAGETHRESHOLD_H_ */
