#include "Utils.h"
#include <vector>

#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define getBits( x )	(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )	(getBits(x[0]) << 4 | getBits(x[1]))

auto NKHook5::Utils::GetModuleBase() -> int
{
	return (int)GetModuleHandle(NULL);
}
auto NKHook5::Utils::GetModuleBaseHandle() -> HMODULE
{
	return GetModuleHandle(NULL);
}
auto NKHook5::Utils::GetBaseModuleSize() -> int
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), GetModuleBaseHandle(), &info, sizeof(info));
	return info.SizeOfImage;
}
auto NKHook5::Utils::GetBaseModuleEnd() -> int
{
	return GetModuleBase() + GetBaseModuleSize();
}
auto NKHook5::Utils::GetThisModule() -> HMODULE
{
	return GetModuleHandleA("NKHook5.dll");
}

auto NKHook5::Utils::FindPattern(const char* pattern) -> int
{
	return FindPattern(GetModuleBase(), GetBaseModuleEnd(), pattern);
}

struct SearchedSig {
	size_t rangeStart;
	size_t rangeEnd;
	std::string pattern;
	uintptr_t result;
	SearchedSig(size_t rangeStart, size_t rangeEnd, std::string pattern, uintptr_t result) {
		this->rangeStart = rangeStart;
		this->rangeEnd = rangeEnd;
		this->pattern = pattern;
		this->result = result;
	}
};

static std::vector<SearchedSig> alreadySearched = std::vector<SearchedSig>();
auto NKHook5::Utils::FindPattern(size_t rangeStart, size_t rangeEnd, const char* pattern) -> size_t {
	for (int i = 0; i < alreadySearched.size(); i++) {
		SearchedSig searched = alreadySearched[i];
		if (searched.pattern == std::string(pattern) && searched.rangeStart == rangeStart && searched.rangeEnd == rangeEnd) {
			return searched.result;
		}
	}
	std::string sanitizedPat = pattern;
	int skips = 0;
	while (sanitizedPat[0] == '?' && sanitizedPat[1] == '?') {
		sanitizedPat = sanitizedPat.substr(3);
		skips++;
		///printf("Sig skips: %d\n", skips);
		//printf("Current sig: %s\n", sanitizedPat.c_str());
	}
	const char* pat = sanitizedPat.c_str();
	long long firstMatch = 0;
	for (long long pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) {
				firstMatch += -skips;
				alreadySearched.push_back(SearchedSig(rangeStart, rangeEnd, std::string(pattern), firstMatch));
				return firstMatch;
			};
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else {
			pat = sanitizedPat.c_str();
			firstMatch = 0;
		}
	}
	//printf("Signature failure: %s\n", pattern);
	return 0;
}

auto NKHook5::Utils::GetTypeName(void* object) -> std::string
{
	void* vtable = *(void**)object;
	void** metaPtr = (void**)((size_t)vtable-(size_t)sizeof(void*));
	void** typeDesc = (void**)((size_t)*metaPtr+(sizeof(void*)*3));
	char* name = (char*)((size_t)*typeDesc+(sizeof(void*)*3));
	return std::string(name);
}