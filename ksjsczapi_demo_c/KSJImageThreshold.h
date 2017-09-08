/*
 * KSJImageThreshold.h
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */

#ifndef KSJIMAGETHRESHOLD_H_
#define KSJIMAGETHRESHOLD_H_


// 二值化图像
// nMode = 0时， >= nThreshold的像素为255， < nThreshold的像素为0
// nMode = 1时， >= nThreshold的像素为0，   < nThreshold的像素为255
// 将改变pData
int KSJIMAGE_Y8_ThresholdSingle(unsigned char *pData, int nWidth, int nHeight, int nThreshold, int nMode);
// 只针对AOI进行二值化
int KSJIMAGE_Y8_ThresholdSingle_AOI(unsigned char *pData, int nWidth, int nHeight, int nThreshold, int nMode, int nAoiX, int nAoiY, int nAoiW, int nAoiH);


// nMode = 0时， >= nThresholdLow && <= nThresholdHig的像素为255，其他为0
// nMode = 1时， >= nThresholdLow && <= nThresholdHig的像素为0，其他为255
// 将改变pData
int KSJIMAGE_Y8_ThresholdDouble(unsigned char *pData, int nWidth, int nHeight, int nThresholdLow, int nThresholdHig, int nMode);
int KSJIMAGE_Y8_ThresholdDouble_AOI(unsigned char *pData, int nWidth, int nHeight, int nThresholdLow, int nThresholdHig, int nMode, int nAoiX, int nAoiY, int nAoiW, int nAoiH);

#endif /* KSJIMAGETHRESHOLD_H_ */
