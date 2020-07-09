#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include "NKH/SDK/CBloonsTD5Game.h"

class Utils
{
public:
	static int getModuleBase();
	static HMODULE getModuleBaseHandle();
	static int getBaseModuleSize();
	static int getBaseModuleEnd();
	static HMODULE getThisModule();
	static DWORD findPattern(DWORD rangeStart, DWORD rangeEnd, const char* pattern);
	static void UnprotectMem(void* addr, int len);
	static bool Detour32(void* src, void* dst, int len);
	static CBloonsTD5Game* getGame();
};