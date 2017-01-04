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
#include "KSJSCZAPIBase.h"
#include "KSJSCZApiTriggerMode.h"
#include "KSJQTApiBase.h"
#include "KSJImageThreshold.h"
#include "KSJImageHistgram.h"
#include "KSJImageAoi.h"

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



static void OnTrackBar_Gain(int nPos)
{
	KSJSCZ_SetGain(0, nPos);
}

//static void OnTrackBar_ExposureLine(int nPos)
//{
//	KSJSCZ_SetExposureLines(0, nPos);
//}

static void OnSpin_ExposureLine(int nPos)
{
	KSJSCZ_SetExposureLines(0, nPos);
}

static void OnSpin_ColStart(int nPos)
{
	unsigned long ulColStart,ulRowStart,ulColSize, ulRowSize;
	KSJSCZ_GetCaptureFieldOfView(0,&ulColStart,&ulRowStart,&ulColSize,&ulRowSize);
	KSJSCZ_SetCaptureFieldOfView(0, nPos, ulRowStart, ulColSize, ulRowSize);
}

static void OnSpin_ColSize(int nPos)
{
	unsigned long ulColStart,ulRowStart,ulColSize, ulRowSize;
	KSJSCZ_GetCaptureFieldOfView(0,&ulColStart,&ulRowStart,&ulColSize,&ulRowSize);
	KSJSCZ_SetCaptureFieldOfView(0, ulColStart, ulRowStart, nPos, ulRowSize);
}

static void OnSpin_RowStart(int nPos)
{
	unsigned long ulColStart,ulRowStart,ulColSize, ulRowSize;
	KSJSCZ_GetCaptureFieldOfView(0,&ulColStart,&ulRowStart,&ulColSize,&ulRowSize);
	KSJSCZ_SetCaptureFieldOfView(0, ulColStart, nPos, ulColSize, ulRowSize);
}

static void OnSpin_RowSize(int nPos)
{
	unsigned long ulColStart,ulRowStart,ulColSize, ulRowSize;
	KSJSCZ_GetCaptureFieldOfView(0,&ulColStart,&ulRowStart,&ulColSize,&ulRowSize);
	KSJSCZ_SetCaptureFieldOfView(0, ulColStart, ulRowStart, ulColSize, nPos);
}

static void OnComboBox_TriggerMode(int pos)
{
	KSJSCZ_TriggerModeSet(0, pos);
}

int main()
{
	int nRet;

	nRet = KSJSCZ_Init();

	int nMaj1,nMaj2,nMin1,nMin2;
	KSJSCZ_GetLibVersion(&nMaj1,&nMaj2,&nMin1,&nMin2);
	printf("LibVersion %d.%d.%d.%d",nMaj1,nMaj2,nMin1,nMin2);

	enum KSJSCZ_DEVICE_TYPE DeviceType;
	unsigned long ulPLVersion;
	KSJSCZ_GetDeviceInformation(&DeviceType, &ulPLVersion);
	printf("DeviceType %d,PLVersion %lu\n",DeviceType,ulPLVersion);

	enum KSJSCZ_TRIGGER_MODE  TriggerMode = KSJSCZ_TM_CMD_SINGLE;
	KSJSCZ_TriggerModeSet(0, TriggerMode );

	unsigned long ulColSizeMin;
	unsigned long ulRowSizeMin;
	unsigned long ulColSizeMax;
	unsigned long ulRowSizeMax;
	KSJSCZ_GetCaptureFieldOfViewRange(0,&ulColSizeMin,&ulRowSizeMin,&ulColSizeMax,&ulRowSizeMax);
	printf("KSJSCZ_GetCaptureFieldOfViewRange ColSizeMin %lu,RowSizeMin %lu,ColSizeMax %lu,RowSizeMax %lu\n",
			ulColSizeMin,ulRowSizeMin,ulColSizeMax,ulRowSizeMax);

	unsigned long ulColStart,ulRowStart,ulColSize, ulRowSize;
	KSJSCZ_GetCaptureFieldOfView(0,&ulColStart,&ulRowStart,&ulColSize,&ulRowSize);
	printf("KSJSCZ_GetCaptureFieldOfView ulColStart %lu,ulRowStart %lu,ulColSize %lu,ulRowSize %lu\n",
			ulColStart,ulRowStart,ulColSize, ulRowSize);

	int  nCaptureWidth, nCaptureHeight, nCaptureBitCount;
	KSJSCZ_GetCaptureSize(0, &nCaptureWidth, &nCaptureHeight, &nCaptureBitCount);
	printf("CaptureSize Width %d,Height %d,BitCount %d\n", nCaptureWidth, nCaptureHeight, nCaptureBitCount);

	unsigned long ulValue,ulMin,ulMax;
	KSJSCZ_GetGainRange(0,&ulMin,&ulMax);
	printf("KSJSCZ_GetGainRange Min %lu,Max %lu\n",ulMin,ulMax);
	KSJSCZ_GetGain(0,&ulValue);
	printf("KSJSCZ_GetGain %lu\n",ulValue);

	KSJSCZ_GetExposureLinesRange(0,&ulMin,&ulMax);
	printf("KSJSCZ_GetExposureLinesRange Min %lu,Max %lu\n",ulMin,ulMax);
	KSJSCZ_GetExposureLines(0,&ulValue);
	printf("KSJSCZ_GetExposureLines %lu\n",ulValue);

	float fExposureTime,fExposureMin,fExposureMax;
	KSJSCZ_GetExposureTimeRange(0,&fExposureMin,&fExposureMax);
	printf("KSJSCZ_GetExposureTimeRange Min %f,Max %f\n",fExposureMin,fExposureMax);
	KSJSCZ_GetExposureTime(0,&fExposureTime);
	printf("KSJSCZ_GetExposureTime %f\n",fExposureTime);

	KSJSCZ_SetExposureLines(0,200);

	unsigned char *pDataBuffer = NULL;

	nRet = KSJQT_Open();
    printf("KSJQT_Open %d\n", nRet);

	KSJQT_SetVideoWidgetPos(0, 0, 640, 480);

	// Gain Trackbar
	KSJSCZ_GetGainRange(0,&ulMin,&ulMax);
	printf("KSJSCZ_GetGainRange Min %lu,Max %lu\n",ulMin,ulMax);
	KSJSCZ_GetGain(0,&ulValue);
	printf("KSJSCZ_GetGain %lu\n",ulValue);
	KSJQT_CreateTrackBar("Gain:", (int*)(&ulValue), ulMax, OnTrackBar_Gain, NULL);

    // Exposure Lines
	KSJSCZ_GetExposureLinesRange(0,&ulMin,&ulMax);
	printf("KSJSCZ_GetExposureLinesRange Min %lu,Max %lu\n",ulMin,ulMax);
	KSJSCZ_GetExposureLines(0,&ulValue);
	printf("KSJSCZ_GetExposureLines %lu\n",ulValue);
	KSJQT_CreateSpinBox("Exposure Lines:", (int*)(&ulValue), (int)ulMax, OnSpin_ExposureLine, NULL);
	// Exposure Lines Trackbar
	// KSJQT_CreateTrackBar("Exposure Lines:", (int*)(&ulValue), ulMax, OnTrackBar_ExposureLine, NULL);

	KSJSCZ_GetCaptureFieldOfViewRange(0,&ulColSizeMin,&ulRowSizeMin,&ulColSizeMax,&ulRowSizeMax);
	printf("KSJSCZ_GetCaptureFieldOfViewRange ColSizeMin %lu,RowSizeMin %lu,ColSizeMax %lu,RowSizeMax %lu\n",
			ulColSizeMin,ulRowSizeMin,ulColSizeMax,ulRowSizeMax);

	KSJSCZ_GetCaptureFieldOfView(0,&ulColStart,&ulRowStart,&ulColSize,&ulRowSize);
	printf("KSJSCZ_GetCaptureFieldOfView ulColStart %lu,ulRowStart %lu,ulColSize %lu,ulRowSize %lu\n",
			ulColStart,ulRowStart,ulColSize, ulRowSize);
	KSJQT_CreateSpinBox("ColStart", (int*)(&ulColStart), ulColSizeMax,   OnSpin_ColStart, NULL);
	KSJQT_CreateSpinBox("ColSize",  (int*)(&ulColSize),  ulColSizeMax,   OnSpin_ColSize,  NULL);
	KSJQT_CreateSpinBox("RowStart", (int*)(&ulRowStart), ulRowSizeMax,   OnSpin_RowStart, NULL);
	KSJQT_CreateSpinBox("RowSize",  (int*)(&ulRowSize),  ulRowSizeMax,   OnSpin_RowSize,  NULL);


	// Trigger Mode ComboBox
	const char *ComboItem_TriggerMode[] =
	{
	    "command continue",
	    "command single",
	    "level high",
	    "level low",
	    "edge positive",
	    "edge negative",
	};

	KSJSCZ_TriggerModeGet(0, (unsigned long*)&TriggerMode);
	KSJQT_CreateComboBox("Trigger Mode:",(int*)(&TriggerMode) , 6, ComboItem_TriggerMode, OnComboBox_TriggerMode, NULL);

    nRet = KSJQT_SetPosition( 0, 0, 640, 480 );

    int nFramesCounter = 0;
    struct timeval  start;
    struct timeval  end;
    float  fTimeUseMs;

    char   szCommand[64];
	while(1)
	{
	    gettimeofday( &start, NULL);

	    nRet = KSJSCZ_CaptureData(0,&pDataBuffer);
	    printf("KSJSCZ_CaptureData %d\n", nRet);

	    MyProcessData(pDataBuffer, nCaptureWidth, nCaptureHeight, nCaptureBitCount);

	    // KSJSCZ_HelperSaveToBmp(pDataBuffer, nCaptureWidth, nCaptureHeight,nCaptureBitCount, "/picture/data/capture.bmp" );

	    nRet = KSJQT_Show(pDataBuffer, nCaptureWidth, nCaptureHeight, nCaptureBitCount);
	    printf("KSJQT_Show %d\n", nRet);

	    nRet = KSJSCZ_ReleaseBuffer(0);
		printf("KSJSCZ_ReleaseBuffer %d\n", nRet);

		gettimeofday(&end, NULL);

		fTimeUseMs = ( end.tv_sec - start.tv_sec ) * 1000 + (end.tv_usec - start.tv_usec) / 1000;

		printf("time use %0.2f ms\n", fTimeUseMs);

		nFramesCounter++;
	}

	KSJQT_Close();
	KSJSCZ_UnInit();

	return 0;
}


