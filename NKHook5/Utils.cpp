#include "Utils.hpp"

#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define getBits( x )	(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )	(getBits(x[0]) << 4 | getBits(x[1]))

auto Utils::getModuleBase() -> int {
	return (int)GetModuleHandle(NULL);
}
auto Utils::getModuleBaseHandle() -> HMODULE {
	return GetModuleHandle(NULL);
}
auto Utils::getBaseModuleSize() -> int
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), getModuleBaseHandle(), &info, sizeof(info));
	return info.SizeOfImage;
}
auto Utils::getBaseModuleEnd() -> int {
	return getModuleBase() + getBaseModuleSize();
}
auto Utils::getThisModule() -> HMODULE {
	return GetModuleHandleA("NKHook5.dll");
}

auto Utils::findPattern(const char* pattern) -> int {
	return findPattern(getModuleBase(), getBaseModuleEnd(), pattern);
}

auto Utils::findPattern(int rangeStart, int rangeEnd, const char* pattern) -> int
{
	const char* pat = pattern;
	int firstMatch = 0;
	for (int pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(char*)pat == '\?' || *(char*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(short*)pat == '\?\?' || *(short*)pat != '\?') pat += 3;
			else pat += 2;	//one ?
		}
		else {
			pat = pattern;
			firstMatch = 0;
		}
	}
	return 0;
}

