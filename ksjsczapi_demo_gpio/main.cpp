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

#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>   
#include <sys/types.h>   
#include <fcntl.h>   
#include <sys/stat.h>   
#include <stdio.h>   
#include <sys/param.h>   
#include <sys/ioctl.h>   
#include <stdlib.h>   
#include <stdio.h>
#include <iostream> 
#include <sys/socket.h>   
#include <arpa/inet.h>   
#include <linux/soundcard.h>   
#include "sys/select.h"   
#include "termios.h"
#include <sys/mman.h>


#include "../ksjsczapi_include/KSJSczApiShow.h"
#include "../ksjsczapi_include/KSJSCZApiBase.h"
#include "../ksjsczapi_include/KSJSCZApiTriggerMode.h"
#include "../ksjsczapi_include/KSJSCZApiIo.h"
#include "../ksjsczapi_include/KSJSczApiCode.h"
#include "../ksjsczapi_include/KSJSczApiInternal.h"

int main(int argc, char **argv)
{
	// 1、初始化KSJSCZ库
	int nRet = KSJSCZ_Init();

	unsigned short usGpioInNum, usGpioOutNum;

	KSJSCZ_GpioGetNum(&usGpioInNum, &usGpioOutNum);

	printf("===== usGpioInNum:%d usGpioOutNum:%d =====\r\n", usGpioInNum, usGpioOutNum);

	int i;
	bool bValue;

	while (1)
	{
		//A Led
		//KSJSCZ_GpioSet(8, false);
		//KSJSCZ_GpioSet(9, false);
		//printf("===== 0  0 =====\r\n");
		//usleep(2000000);
		//KSJSCZ_GpioSet(8, false);
		//KSJSCZ_GpioSet(9, true);
		//printf("===== 0  1 =====\r\n");
		//usleep(2000000);
		//KSJSCZ_GpioSet(8, true);
		//KSJSCZ_GpioSet(9, false);
		//printf("===== 1  0 =====\r\n");
		//usleep(2000000);
		//KSJSCZ_GpioSet(8, true);
		//KSJSCZ_GpioSet(9, true);
		//printf("===== 1  1 =====\r\n");
		//usleep(2000000);

		printf("===== Set out ports to 0 =====\r\n");
		for (i = usGpioInNum; i < usGpioInNum + usGpioOutNum; ++i)
		{
			KSJSCZ_GpioSet(i, false);
		}
		usleep(2000000);

		for (i = usGpioInNum; i < usGpioInNum + usGpioOutNum; ++i)
		{
			printf("===== Set out port %d to 1 =====\r\n", i + 1);
			KSJSCZ_GpioSet(i, true);
			usleep(2000000);
			printf("===== Set out port %d to 0 =====\r\n", i + 1);
			KSJSCZ_GpioSet(i, false);
			usleep(2000000);
		}

		printf("===== Set out ports to 1 =====\r\n");
		for (i = usGpioInNum; i < usGpioInNum + usGpioOutNum; ++i)
		{
			KSJSCZ_GpioSet(i, true);
		}
		usleep(2000000);

		for (i = usGpioInNum; i < usGpioInNum + usGpioOutNum; ++i)
		{
			printf("===== Set out port %d to 0 =====\r\n", i + 1);
			KSJSCZ_GpioSet(i, false);
			usleep(2000000);
			printf("===== Set out port %d to 1 =====\r\n", i + 1);
			KSJSCZ_GpioSet(i, true);
			usleep(2000000);
		}

		for (i = 0; i < usGpioInNum; ++i)
		{
			printf("===== Get in port %d value =====\r\n", i + 1);
			KSJSCZ_GpioGet(i, &bValue);
			printf("===== Port %d value is:%d =====\r\n", i + 1, bValue);
			usleep(2000000);
		}

		//usleep(5000000);
	}

	KSJSCZ_UnInit();

	return 0;
}


