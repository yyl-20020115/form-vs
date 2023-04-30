#include "utils.h"
#ifdef WINDOWS
#include <windows.h>

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
    exit(0);
}
unsigned int alarm(unsigned int seconds)
{
    HANDLE hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        return 0;
    }
    HANDLE hTimer = 0;
    // Set a timer to call the timer routine in 10 seconds.
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
        (WAITORTIMERCALLBACK)TimerRoutine, 0, seconds*1000, 0, 0))
    {
        return 0;
    }

	return seconds;
}
#endif