#ifndef CCA04C04_B581_4D3C_A60B_B29CB543C323
#define CCA04C04_B581_4D3C_A60B_B29CB543C323

#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>

class Utils {
public:
    static auto getModuleBase() -> int;
	static auto getModuleBaseHandle() -> HMODULE;
	static auto getBaseModuleSize() -> int;
	static auto getBaseModuleEnd() -> int;
	static auto getThisModule() -> HMODULE;
    static auto findPattern(const char* pattern) -> int;
    static auto findPattern(int rangeStart, int rangeEnd, const char* pattern) -> int;
};
#endif /* CCA04C04_B581_4D3C_A60B_B29CB543C323 */
