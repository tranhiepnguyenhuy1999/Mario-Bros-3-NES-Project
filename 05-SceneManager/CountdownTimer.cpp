#include "CountdownTimer.h"
#include <Windows.h>
void CountdownTimer::countdownTime() {
	while (counter >= 1)
	{
		//Sleep(1000);
		counter--;
	}
}
CountdownTimer* CountdownTimer::__instance = NULL;
CountdownTimer* CountdownTimer::GetInstance()
{
	if (__instance == NULL) __instance = new CountdownTimer();
	return __instance;
}