/*
 * main.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: GTY
 */
#include "xf_headers.h"
#include "xf_AutoThreshold_config.h"
#include "KSJSczApiShow.h"
#include "KSJSCZApiBase.h"
#include "KSJSCZApiTriggerMode.h"
#include "KSJSCZApiIo.h"
#include "KSJSczApiCode.h"
#include "KSJSczApiInternal.h"
#include <sys/time.h>


int main(int argc,char **argv)
{
	//…Ë÷√œ‡ª˙
	KSJSCZ_Init();
	KSJSCZ_SetTriggerMode(0, KSJSCZ_TM_CMD_CONTINUE );
	KSJSCZ_SetCaptureFieldOfView(0, (1280 - 640) / 2, (1024 - 480) / 2, 640, 480);
	KSJSCZ_SetGain(0, 128);
	KSJSCZ_SetExposureLines(0, 800);

	KSJSCZ_SetVideoWidgetPos(0, 0, 0, 1280, 480);
	KSJSCZ_SetPosition(0, 0, 0, 1280, 480);

	unsigned char *pDataBuffer=NULL;
	unsigned char *pDisplayBuffer=NULL;
	unsigned char Otsuval=0;
	KSJSCZ_Malloc(1280*480, &pDisplayBuffer);

	while(1)
	{
		KSJSCZ_CaptureData(0, &pDataBuffer);

		xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> imgInput(480,640);
		xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> imgOutput(480,640);
		imgInput.copyTo(pDataBuffer);

		struct timeval  start;
		struct timeval  end;
		gettimeofday(&start, NULL);

		otsuthreshold_accel(imgInput,Otsuval);
		threshold_accel(imgInput,imgOutput,Otsuval);

		gettimeofday(&end, NULL);
		float m_fRunTimeMs = (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;

		printf("Times: %f ms \n", m_fRunTimeMs);
		cv::Mat in(480,640,CV_8UC1,imgInput.copyFrom());
		cv::Mat out(480,640,CV_8UC1,imgOutput.copyFrom());
		cv::Mat Result;
		cv::hconcat(in,out,Result);
		memcpy(pDisplayBuffer,Result.data,1280*480);
		KSJSCZ_ShowUserLoadData(0,pDisplayBuffer,1280 ,480, 8);
		KSJSCZ_ReleaseBuffer(0);

	}
	KSJSCZ_Free(&pDisplayBuffer);
	return 0;
}


