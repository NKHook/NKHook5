#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "SDK/WinInput.h"
#include "SDK/CBloonEscapedEvent.h"
#include "SDK/CTowerManager.h"
#include "SDK/CBaseTower.h"

#include "Blue/Chai.h"

using namespace std;
typedef uint32_t uint;

/*Register saving shit*/
int the_registers[8];
int saveRegisters_jmpBack = 0;
void __declspec(naked) saveRegisters() {
	__asm {
		mov the_registers[0 * 4], eax
		mov the_registers[1 * 4], ebx
		mov the_registers[2 * 4], ecx
		mov the_registers[3 * 4], edx
		mov the_registers[4 * 4], esi
		mov the_registers[5 * 4], edi
		mov the_registers[6 * 4], ebp
		mov the_registers[7 * 4], esp

		jmp saveRegisters_jmpBack;
	}
}
int restoreRegisters_jmpBack = 0;
void __declspec(naked) restoreRegisters() {
	__asm {
		mov eax, the_registers[0 * 4]
		mov ebx, the_registers[1 * 4]
		mov ecx, the_registers[2 * 4]
		mov edx, the_registers[3 * 4]
		mov esi, the_registers[4 * 4]
		mov edi, the_registers[5 * 4]
		mov ebp, the_registers[6 * 4]
		mov esp, the_registers[7 * 4]

		jmp restoreRegisters_jmpBack
	}
}


/*Hooks*/
int gameInstanceTickHookThingIdfkJmpBack = 0;
void __declspec(naked) __fastcall gameInstanceTickHookThingIdfkCallback() {
	__asm {
		push eax;
		mov eax, saveRegistersJmpBack;
		mov[saveRegisters_jmpBack], eax;
		pop eax;
		jmp saveRegisters;
	saveRegistersJmpBack:
	}
	Utils::updateGameBase(the_registers[2]);
	__asm {
		push eax;
		mov eax, restoreRegistersJmpBack;
		mov[restoreRegisters_jmpBack], eax;
		pop eax;
		jmp restoreRegisters;
	RestoreRegistersJmpBack:
	}
	__asm {
		mov eax, [ecx]
		call dword ptr[eax + 0x38]

		jmp gameInstanceTickHookThingIdfkJmpBack;
	}
}


typedef void (__fastcall* Keypressed)(WinInput* self, int param_1, char key);
Keypressed keypressed_original;
void __fastcall keypressedCallback(WinInput* self, int param_1, char key) {
	Chai::invokeKeyCallbacks(key);
	return keypressed_original(self, param_1, key);
}

int bloonEscapedJmpBack = 0;
void __declspec(naked) bloonEscapedCallback() {
	__asm {
		push eax;
		mov eax, saveRegistersJmpBack;
		mov [saveRegisters_jmpBack], eax;
		pop eax;
		jmp saveRegisters;
	saveRegistersJmpBack:
	}
	Chai::invokeBloonEscapedCallbacks(*((CBloonEscapedEvent*)the_registers[1]));
	__asm {
		push eax;
		mov eax, restoreRegistersJmpBack;
		mov [restoreRegisters_jmpBack], eax;
		pop eax;
		jmp restoreRegisters;
	RestoreRegistersJmpBack:
	}
	__asm {
		push ebp
		mov ebp, esp
		push - 01

		jmp [bloonEscapedJmpBack]
	}
}

int upgradeTowerJmpBack = 0;
void __declspec(naked) upgradeTowerCallback() {
	__asm {
		push eax;
		mov eax, saveRegistersJmpBack;
		mov[saveRegisters_jmpBack], eax;
		pop eax;
		jmp saveRegisters;
	saveRegistersJmpBack:
	}
	Chai::invokeTowerUpgradedCallbacks(*((CTowerManager*)the_registers[2]), **((CBaseTower**)(the_registers[7]+0x4)), *((int*)(the_registers[7]+0x8)));
	__asm {
		push eax;
		mov eax, restoreRegistersJmpBack;
		mov[restoreRegisters_jmpBack], eax;
		pop eax;
		jmp restoreRegisters;
	RestoreRegistersJmpBack:
	}
	__asm {
		push ebp
		mov ebp, esp
		and esp, -0x08

		jmp [upgradeTowerJmpBack]
	}
}

typedef LRESULT(WINAPI* DispatchMessageW_Original)(const MSG* lpMsg);
DispatchMessageW_Original dispatchMessageW_Original;
LRESULT WINAPI DispatchMessageW_Callback(const MSG* lpMsg) {
	//cout << hex << lpMsg->message << endl;
	return dispatchMessageW_Original(lpMsg);
}


PAINTSTRUCT ps;
HDC hdc;

typedef BOOL(WINAPI* PeekMessageW_Original)(LPMSG lpMsg, HWND hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);
PeekMessageW_Original peekMessageW_Original;
BOOL WINAPI PeekMessageW_Callback(LPMSG lpMsg, HWND hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg) {
	cout << hex << lpMsg->message << endl;
	BOOL ret = peekMessageW_Original(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	return ret;
}


Hooks::Hooks()
{
	if (MH_Initialize() != MH_OK) {
		cout << "Failed to initialize minhook!" << endl;
		return;
	}

	/*Game Instance tick hook thing*/
	int gameInstanceTickHookThingIdfk = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "85 C0 7E 16 83 F8") - 5;
	Utils::Detour32((void*)gameInstanceTickHookThingIdfk, &gameInstanceTickHookThingIdfkCallback, 5);
	gameInstanceTickHookThingIdfkJmpBack = gameInstanceTickHookThingIdfk + 5;

	/*Keypress hook*/
	int keypressed = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "8B 7D 08 8B D9 81 FF 00 01 00 00 73 3A") - 5;
	if (MH_CreateHook((void*)keypressed, &keypressedCallback, reinterpret_cast<LPVOID*>(&keypressed_original))==MH_OK) {
		if (MH_EnableHook((void*)keypressed)==MH_OK) {
			//cout << "Keypressed hook created!" << endl;
		}
		else {
			cout << "Failed to enable keypressed hook" << endl;
		}
	}
	else {
		cout << "Failed to create keypressed hook!" << endl;
	}

	/*Bloon escaped hook*/
	int bloonEscaped = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "68 64 BF ?? ?? 64 A1") - 5;
	Utils::Detour32((void*)bloonEscaped, &bloonEscapedCallback, 5);
	bloonEscapedJmpBack = bloonEscaped + 0x5;

	/*Tower upgraded*/
	int upgradeTower = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "83 EC 44 53 8B 5D 08 8B") - 6;
	Utils::Detour32((void*)upgradeTower, &upgradeTowerCallback, 6);
	upgradeTowerJmpBack = upgradeTower + 6;

	/*game main hook (ignore)*/
	int gameMain = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8B EC 6A FF 68 CF 5F");

	/*Dispatch message hook*/
	if (MH_CreateHook(&DispatchMessageW, &DispatchMessageW_Callback, reinterpret_cast<LPVOID*>(&dispatchMessageW_Original)) == MH_OK) {
		if (MH_EnableHook(&DispatchMessageW) == MH_OK) {
			cout << "DispatchMessageW hook created!" << endl;
		}
		else {
			cout << "Failed to enable DispatchMessageW hook" << endl;
		}
	}
	else {
		cout << "Failed to create DispatchMessageW hook!" << endl;
	}
	
	/*Dispatch message hook*/
	if (MH_CreateHook(&PeekMessageW, &PeekMessageW_Callback, reinterpret_cast<LPVOID*>(&peekMessageW_Original)) == MH_OK) {
		if (MH_EnableHook(&PeekMessageW) == MH_OK) {
			cout << "PeekMessageW hook created!" << endl;
		}
		else {
			cout << "Failed to enable PeekMessageW hook" << endl;
		}
	}
	else {
		cout << "Failed to create PeekMessageW hook!" << endl;
	}
}