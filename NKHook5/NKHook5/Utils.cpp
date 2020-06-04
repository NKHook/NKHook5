#include "pch.h"
#include "Utils.h"
#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define getBits( x )	(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )	(getBits(x[0]) << 4 | getBits(x[1]))

int Utils::getModuleBase() {
	return (int)GetModuleHandle(NULL);
}
HMODULE Utils::getModuleBaseHandle() {
	return GetModuleHandle(NULL);
}
int Utils::getBaseModuleSize()
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), getModuleBaseHandle(), &info, sizeof(info));
	return info.SizeOfImage;
}
int Utils::getBaseModuleEnd() {
	return getModuleBase() + getBaseModuleSize();
}
HMODULE Utils::getThisModule() {
	return GetModuleHandleA("NKHook5.dll");
}

DWORD Utils::findPattern(DWORD rangeStart, DWORD rangeEnd, const char* pattern)
{
	const char* pat = pattern;
	DWORD firstMatch = 0;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;	//one ?
		}
		else {
			pat = pattern;
			firstMatch = 0;
		}
	}
	return NULL;
}