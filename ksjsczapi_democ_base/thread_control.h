/*
 * thread_control.h
 *
 *  Created on: 2016-10-26
 *      Author: Mike
 */

#ifndef THREAD_CONTROL_H_
#define THREAD_CONTROL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/sem.h>

#define KILL_TIMEOUT     5



void SendSemphore(void);
void WatiSemphore(void);
int  CreateThread(const char *szName, void* pEntryFunc(void*), unsigned int Arg);
int  KillThread();
int  IsThreadKilled();
void DisableTimer() ;
void EnableTimer();
void TimeoutHandler(int signo);

#endif /* THREAD_CONTROL_H_ */
