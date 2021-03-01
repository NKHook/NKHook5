#include "Utils.h"

#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define getBits( x )	(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )	(getBits(x[0]) << 4 | getBits(x[1]))

auto NKHook5::Utils::getModuleBase() -> int {
	return (int)GetModuleHandle(NULL);
}
auto NKHook5::Utils::getModuleBaseHandle() -> HMODULE {
	return GetModuleHandle(NULL);
}
auto NKHook5::Utils::getBaseModuleSize() -> int
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), getModuleBaseHandle(), &info, sizeof(info));
	return info.SizeOfImage;
}
auto NKHook5::Utils::getBaseModuleEnd() -> int {
	return getModuleBase() + getBaseModuleSize();
}
auto NKHook5::Utils::getThisModule() -> HMODULE {
	return GetModuleHandleA("NKHook5.dll");
}

auto NKHook5::Utils::findPattern(const char* pattern) -> int {
	return findPattern(getModuleBase(), getBaseModuleEnd(), pattern);
}

auto NKHook5::Utils::findPattern(int rangeStart, int rangeEnd, const char* pattern) -> int
{
	const char* pat = pattern;
	DWORD firstMatch = 0;
	for (int pCur = rangeStart; pCur < rangeEnd; pCur++)
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

