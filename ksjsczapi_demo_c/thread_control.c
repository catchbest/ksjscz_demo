#include "thread_control.h"


static sem_t     *gpSemID   = NULL;
static pthread_t  gThreadid = -1;

/*
* 鍦ㄨ繘绋嬩腑璋冪敤鏈嚱鏁帮紝鍒涘缓涓庣嚎绋嬮�氳鐢ㄧ殑淇″彿閲�
*/
int CreateSemphore(void)
{
	sem_unlink("kill_sem");
	gpSemID = sem_open("kill_sem", O_CREAT|O_EXCL, 0644, 0);
	if(SEM_FAILED == gpSemID)
	{
		return -1;  
	}
	sem_init(gpSemID, 1, 0);
	return 0;
}

/*
* 杩涚▼璋冪敤鏈嚱鏁帮紝缁欑嚎绋嬪彂閫佷俊鍙烽噺
*/
void SendSemphore(void)
{
	if(NULL == gpSemID) return;

	sem_post(gpSemID);
}

/*
* 绾跨▼搴斿湪鑷繁鐨勪富寰幆涓皟鐢ㄦ湰鍑芥暟锛涙垚鍔熸帴鏀跺埌淇″彿閲忔椂锛岃〃绀鸿繘绋嬪彂鍑轰簡鎸囦护锛岃绾跨▼閫�鍑猴紱鏈嚱鏁颁笉浼氶樆濉炵嚎绋�
*/
void WatiSemphore(void)
{
	if(NULL == gpSemID) return;

	if(0 == sem_trywait(gpSemID))
	{
		/*
		* got semphore from process, thread will exit
		*/
		printf("thread (%u) killed by process\n", pthread_self());
		pthread_exit(0);
	}	
}



/*
* 杩涚▼鍦ㄩ渶瑕佹椂锛岃皟鐢ㄦ湰鍑芥暟寮烘潃绾跨▼
*/
int KillThread( )
{
	if(0 != pthread_cancel(gThreadid))
	{
		printf("Fail to kill thread (%u)(%s)\n", gThreadid, (strerror(errno)));
		return -1;
	}
	
	return 0;
}

/*
* 杩涚▼閫氳繃鏈嚱鏁帮紝鍙緱鐭ョ嚎绋嬫槸鍚﹁繕鍦ㄨ繍琛岋紱
* 杩斿洖0鏃讹紝琛ㄧず杩樺湪杩愯
*/
int IsThreadKilled()
{
	return pthread_kill(gThreadid, 0);
}

/*
* 杩欐槸涓�涓渶绠�鍗曠殑绾跨▼锛屽彧鎺ユ敹杩涚▼鍙戞潵鐨勪俊鍙烽噺鍙婁紤鐪狅紱
* 鎺ユ敹鍒拌繘绋嬪彂鏉ョ殑淇″彿閲忓悗锛岀嚎绋嬩究鐩存帴閫�鍑轰簡
*/




/*
* 鏈嚱鏁扮敤浜庡紑鍚痶imer锛屾瘡涓懆鏈熷彂鍑轰竴涓猄IGALRM淇″彿
*/
void EnableTimer()
{
	struct itimerval value;

	value.it_value.tv_sec  = KILL_TIMEOUT;
	value.it_value.tv_usec = 0;
	value.it_interval      = value.it_value;

	setitimer(ITIMER_REAL, &value, NULL);
}

/*
* 鏈嚱鏁颁娇timer澶辨晥锛屽嵆涓嶅啀鎸夊懆鏈熷彂鍑篠IGALRM淇″彿
*/
void DisableTimer()
{
	struct itimerval value;

	value.it_value.tv_sec  = 0;
	value.it_value.tv_usec = 0;
	value.it_interval      = value.it_value;

	setitimer(ITIMER_REAL, &value, NULL);
}

/*
* 姝や负鍛ㄦ湡澶勭悊鍑芥暟锛涘懆鏈熷埌鏃讹紝鎵ц鐗瑰畾鍔ㄤ綔
*/
void TimeoutHandler(int signo)
{
	if(SIGALRM != signo) return;

	if(0 == IsThreadKilled( ))
	{
		printf("TimeoutHandler\n");
		/*
		* since thread can receive signal, so it is still running, kill it
		*/
		KillThread();
		DisableTimer();
	}
}

/*
* 鐢ㄤ簬缁戝畾鍛ㄦ湡鍑芥暟TimeoutHandler鍜孲IGALRM淇″彿
*/
void BindTimerHandler(void)
{
	struct sigaction act;
	// sigset_t         sigset;

	act.sa_handler = TimeoutHandler;
	act.sa_flags   = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, NULL);
}


/*
* 杩涚▼璋冪敤鏈嚱鏁板垱寤虹嚎绋�
*/
int CreateThread(const char *szName, void* pEntryFunc(void*), unsigned int Arg)
{
	int            rtn = -1;
	pthread_attr_t attr;

	if( NULL == pEntryFunc )
	{
		printf("CreateThread failed: pEntryFunc is NULL\n");
		return rtn;
	}

	if(gThreadid != -1)
	{
		printf("error, thread(%u) created already, please kill first!\n" ,gThreadid);
	}

	CreateSemphore();

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	rtn = pthread_create(&gThreadid, &attr, pEntryFunc,(void *)Arg);
	pthread_attr_destroy(&attr);

	if(0 != rtn)
	{
		printf("CreateThread failed: pthread_create err(%d)\n", rtn);
		return rtn;
	}
	else
	{
		printf("CreateThread success id(%u)\n" , gThreadid);
	}

	BindTimerHandler();

	return rtn;
}


/*
* 涓昏繘绋嬶紱姝ｅ父寰幆unWait鍦堝悗锛屽彂閫佷俊鍙烽噺锛岄�氱煡绾跨▼閫�鍑猴紝骞跺悓鏃跺紑鍚痶imer锛岃秴鏃跺彂鐢熷悗锛屽鏋滅嚎绋嬭繕鍦ㄨ繍琛岋紝鍒欒繘琛屽己鏉�鍔ㄤ綔
*/
#if 0
int main(int argc, char **argv)
{
	if(argc < 2) return -1;

	unsigned int unWait = atoi(argv[1]);
	int nKillFlg = 1;

	if(0 != CreateSemphore())
	{
		printf("Fail to create semphore\n");
		return -1;
	}

	if(0 != CreateThread(&gThreadid, "user's thread", ThreadOfUser, 0))
	{
		printf("Fail to create thread\n");
		return -1;
	}

	BindTimerHandler();

	while(1)
	{
		printf("process running (%d)\n", unWait);
		sleep(5);
		if((unWait-- <= 0) && nKillFlg)
		{
			/*
			* when condition matching, the process will kill thread
			*/
			SendSemphore();
			nKillFlg = 0;
			EnableTimer();
		}
	}

	return 0;
}
#endif
