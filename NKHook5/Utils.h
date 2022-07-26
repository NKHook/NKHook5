#ifndef NKHOOK5_UTILS
#define NKHOOK5_UTILS

#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <string>

#define STRING_EXPAND(s) #s
#define STRING(s) STRING_EXPAND(s)

//Define the build ver if CMake failed to or it wasn't build with it
#ifndef NKHOOK_BUILD_VERSION
#define NKHOOK_BUILD_VERSION Unknown
#endif

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
