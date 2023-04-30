#include "utils.h"

#ifdef WINDOWS
#include "config.h"
#include <windows.h>
#include <sources/portsignals.h>

HANDLE hTimerQueue = NULL;
HANDLE hTimer = NULL;

#ifdef TRAPSIGNALS
#ifdef INTSIGHANDLER
//static 
extern int onErrSig(int i);
#else
//static 
extern VOID onErrSig(int i);
#endif

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
#ifdef TRAPSIGNALS
    onErrSig(SIGALRM);
#endif
}
#endif

unsigned int alarm(unsigned int seconds)
{
#ifdef TRAPSIGNALS
    if (NULL == hTimerQueue)
    {
        hTimerQueue = CreateTimerQueue();
    }
    if (seconds == 0 && hTimer!=NULL) {
        CloseHandle(hTimer);
        hTimer = NULL;
    }
    if (hTimerQueue != NULL && CreateTimerQueueTimer(&hTimer, hTimerQueue,
        (WAITORTIMERCALLBACK)TimerRoutine, 0, seconds * 1000, 0, 0)) {
        return seconds;
    }
#endif
    return 0;
}
#endif
