/*
 * main.cpp
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "KSJImageThreshold.h"
#include "KSJImageHistgram.h"
#include "KSJImageAoi.h"

#include "../ksjsczapi_include/KSJSczApiShow.h"
#include "../ksjsczapi_include/KSJSCZApiBase.h"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"
#include "../ksjsczapi_include/KSJSCZApiIo.h"
#include "../ksjsczapi_include/KSJSczApiCode.h"
#include "../ksjsczapi_include/KSJSczApiInternal.h"

void MyProcessData(unsigned char *pData, int nWidth, int nHeight, int nBitCount)
{
    int nHistgramAoiX = nWidth/4;
    int nHistgramAoiY = nHeight/4;
    int nHistgramAoiW = nWidth/2;
    int nHistgramAoiH = nHeight/2;
	int nHistgram[256];

    KSJIMAGE_Y8_Histgram(pData, nWidth, nHeight, nHistgramAoiX, nHistgramAoiY, nHistgramAoiW, nHistgramAoiH, nHistgram);
    KSJIMAGE_ShowAoi(pData, nWidth, nHeight, nBitCount, nHistgramAoiX, nHistgramAoiY, nHistgramAoiW, nHistgramAoiH);

    int nThresholdAoiX = 0;
    int nThresholdAoiY = 0;
    int nThresholdAoiW = 320;
    int nThresholdAoiH = 240;

    // Threshold = 128, mode = 0 >Threshold = HIGH, <Threshold = LOW
    KSJIMAGE_Y8_ThresholdSingle_AOI(pData, nWidth, nHeight, 128, 0, nThresholdAoiX, nThresholdAoiY, nThresholdAoiW, nThresholdAoiH);
}

int main(int argc, char **argv)
{
	int nRet = KSJSCZ_ERR_SUCCESS;

	int nDisplayWidth  = 600;
	int nDisplayHeight = 480;
	int nXPosition     = (1280 - nDisplayWidth) / 2;
	int nYPosition     = (720 - nDisplayHeight) / 2;

	int ulColSize      = 600;
	int ulRowSize      = 480;

	int nGain          = 128;
	int nExposureLines = 10;

	if (argc > 1) nExposureLines = atoi(argv[1]);
	if (argc > 2) nGain          = atoi(argv[2]);
	if (argc > 3) nXPosition     = atoi(argv[3]);
	if (argc > 4) nYPosition     = atoi(argv[4]);
	if (argc > 5) nDisplayWidth  = atoi(argv[5]);
	if (argc > 6) nDisplayHeight = atoi(argv[6]);
	if (argc > 7) ulColSize      = atoi(argv[7]);
	if (argc > 8) ulRowSize      = atoi(argv[8]);

	// 1、初始化KSJSCZ库
	nRet = KSJSCZ_Init();

	// 2、设置触发模式
	enum KSJSCZ_TRIGGER_MODE  TriggerMode = KSJSCZ_TM_CMD_CONTINUE;
	KSJSCZ_SetTriggerMode(0, TriggerMode );

	//KSJSCZ_SetGain(0, nGain);
	//KSJSCZ_SetExposureLines(0, nExposureLines);

	//KSJSCZ_SetFrameBufNum(0, 1);

	// 3A、设置显示位置
	nRet = KSJSCZ_SetVideoWidgetPos(0, nXPosition, nYPosition, nDisplayWidth, nDisplayHeight);
	nRet = KSJSCZ_SetPosition(0, 0, 0, nDisplayWidth, nDisplayHeight);

	// 3、设置图像采集区域
	nRet = KSJSCZ_SetCaptureFieldOfView(0, (1280 - ulColSize) / 2, (1024 - ulRowSize) / 2, ulColSize, ulRowSize);

	// 4A、设置增益和曝光参数
	nRet = KSJSCZ_SetGain(0, nGain);
	nRet = KSJSCZ_SetExposureLines(0, nExposureLines);

	int  nCaptureWidth, nCaptureHeight, nCaptureBitCount;

	// 5、取得采集图像的大小参数，与KSJSCZ_SetCaptureFieldOfView设置有关
	nRet = KSJSCZ_GetCaptureSize(0, &nCaptureWidth, &nCaptureHeight, &nCaptureBitCount);

	unsigned char* pDataBuffer = NULL;

	int nCount = 0;
	char szImageFilePath[260] = { 0 };

	while (1)
	{
		++nCount;

		// 6、采集图像
		nRet = KSJSCZ_CaptureData(0, &pDataBuffer);

		if (nRet == KSJSCZ_ERR_SUCCESS)
		{
			// 7、对采集到的图像进行处理
			MyProcessData(pDataBuffer, nCaptureWidth, nCaptureHeight, nCaptureBitCount);

			// 8、显示
			nRet = KSJSCZ_ShowCaptureData(0, pDataBuffer);

			// 9、释放采集存储区，只有放空采集存储区以后，采集存储区有空区域，才能进行下一次图像采集。
			nRet = KSJSCZ_ReleaseBuffer(0);
		}
	}

	KSJSCZ_UnInit();

	return 0;
}


