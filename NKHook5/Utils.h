#ifndef NKHOOK5_UTILS
#define NKHOOK5_UTILS

#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <string>

namespace NKHook5
{
	class Utils {
	public:
		static auto GetModuleBase() -> int;
		static auto GetModuleBaseHandle() -> HMODULE;
		static auto GetBaseModuleSize() -> int;
		static auto GetBaseModuleEnd() -> int;
		static auto GetThisModule() -> HMODULE;
		static auto FindPattern(const char* pattern) -> int;
		static auto FindPattern(size_t rangeStart, size_t rangeEnd, const char* pattern) -> size_t;
		static auto GetTypeName(void* object) -> std::string;
	};
}
#endif /* NKHOOK5_UTILS */
