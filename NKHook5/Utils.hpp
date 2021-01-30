#ifndef CCA04C04_B581_4D3C_A60B_B29CB543C323
#define CCA04C04_B581_4D3C_A60B_B29CB543C323

#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>

class Utils {
public:
    static int getModuleBase();
	static HMODULE getModuleBaseHandle();
	static int getBaseModuleSize();
	static int getBaseModuleEnd();
	static HMODULE getThisModule();
    static int findPattern(int rangeStart, int rangeEnd, const char* pattern);
};
#endif /* CCA04C04_B581_4D3C_A60B_B29CB543C323 */
