#include "UserInfo.h"

UserInfo* UserInfo::__instance = NULL;

UserInfo* UserInfo::GetInstance()
{
	if (__instance == NULL) __instance = new UserInfo();
	return __instance;
}