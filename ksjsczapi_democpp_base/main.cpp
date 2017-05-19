/*
 * main.cpp
 *
 *  Created on: 2016-10-24
 *      Author: Mike
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

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

	int nDisplayWidth  = 800;
	int nDisplayHeight = 600;
	int nXPosition     = (1280 - nDisplayWidth) / 2;
	int nYPosition     = (720 - nDisplayHeight) / 2;

	int ulColSize      = 800;
	int ulRowSize      = 600;

	int nGain          = 128;
	int nExposureLines = 100;

	if (argc > 2) nXPosition     = atoi(argv[2]);
	if (argc > 3) nYPosition     = atoi(argv[3]);
	if (argc > 4) nDisplayWidth  = atoi(argv[4]);
	if (argc > 5) nDisplayHeight = atoi(argv[5]);
	if (argc > 6) ulColSize      = atoi(argv[6]);
	if (argc > 7) ulRowSize      = atoi(argv[7]);
	if (argc > 8) nGain          = atoi(argv[8]);
	if (argc > 9) nExposureLines = atoi(argv[9]);

	nRet = KSJSCZ_Init();

	enum KSJSCZ_TRIGGER_MODE  TriggerMode = KSJSCZ_TM_CMD_SINGLE;
	KSJSCZ_SetTriggerMode(0, TriggerMode );

	KSJSCZ_SetGain(0, nGain);
	KSJSCZ_SetExposureLines(0, nExposureLines);

	nRet = KSJSCZ_SetVideoWidgetPos(0, nXPosition, nYPosition, nDisplayWidth, nDisplayHeight);
	nRet = KSJSCZ_SetPosition(0, 0, 0, nDisplayWidth, nDisplayHeight);
	nRet = KSJSCZ_SetCaptureFieldOfView(0, (1280 - ulColSize) / 2, (1024 - ulRowSize) / 2, ulColSize, ulRowSize);
	nRet = KSJSCZ_SetGain(0, nGain);
	nRet = KSJSCZ_SetExposureLines(0, nExposureLines);

	int  nCaptureWidth, nCaptureHeight, nCaptureBitCount;

	nRet = KSJSCZ_GetCaptureSize(0, &nCaptureWidth, &nCaptureHeight, &nCaptureBitCount);

	unsigned char* pDataBuffer = NULL;

	int nCount = 0;
	char szImageFilePath[260] = { 0 };

	while (1)
	{
		nRet = KSJSCZ_CaptureData(0, &pDataBuffer);

		if (nRet == KSJSCZ_ERR_SUCCESS)
		{
			MyProcessData(pDataBuffer, nCaptureWidth, nCaptureHeight, nCaptureBitCount);
			nRet = KSJSCZ_ShowCaptureData(0, pDataBuffer);
		}

		nRet = KSJSCZ_ReleaseBuffer(0);
	}

	KSJSCZ_UnInit();

	return 0;
}


