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
#include "SDK/CTextObject.h"

using namespace std;
typedef uint32_t uint;

#pragma region Registers
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
#pragma endregion


#pragma region Hooks

/*Hooks*/
#pragma region GameInstance
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
#pragma endregion
#pragma region Keypressed
typedef void(__fastcall* Keypressed)(WinInput* self, int param_1, char key);
Keypressed keypressed_original;
void __fastcall keypressedCallback(WinInput* self, int param_1, char key) {
	Chai::invokeKeyCallbacks(key);
	return keypressed_original(self, param_1, key);
}
#pragma endregion
#pragma region Bloon Escaped
int bloonEscapedJmpBack = 0;
void __declspec(naked) bloonEscapedCallback() {
	__asm {
		push eax;
		mov eax, saveRegistersJmpBack;
		mov[saveRegisters_jmpBack], eax;
		pop eax;
		jmp saveRegisters;
	saveRegistersJmpBack:
	}
	Chai::invokeBloonEscapedCallbacks(*((CBloonEscapedEvent*)the_registers[1]));
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
		push - 01

		jmp[bloonEscapedJmpBack]
	}
}
#pragma endregion
#pragma region UpgradeTower
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
	Chai::invokeTowerUpgradedCallbacks(*((CTowerManager*)the_registers[2]), **((CBaseTower**)(the_registers[7] + 0x4)), *((int*)(the_registers[7] + 0x8)));
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

		jmp[upgradeTowerJmpBack]
	}
}
#pragma endregion
#pragma region DispatchMessageW
typedef LRESULT(WINAPI* DispatchMessageW_Original)(const MSG* lpMsg);
DispatchMessageW_Original dispatchMessageW_Original;
LRESULT WINAPI DispatchMessageW_Callback(const MSG* lpMsg) {
	//cout << hex << lpMsg->message << endl;
	return dispatchMessageW_Original(lpMsg);
}
#pragma endregion
#pragma region PeekMessageW
typedef BOOL(WINAPI* PeekMessageW_Original)(LPMSG lpMsg, HWND hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);
PeekMessageW_Original peekMessageW_Original;
BOOL WINAPI PeekMessageW_Callback(LPMSG lpMsg, HWND hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg) {
	//cout << hex << lpMsg->message << endl;
	BOOL ret = peekMessageW_Original(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	return ret;
}
#pragma endregion
#pragma region CTextObject Draw
int CTextObject_draw_jmpBack = 0;
bool canRender = false;
//int regEcx;
//bool called = false;
void CTextObjectDrawThingIdek() {
	CTextObject* self = (CTextObject*)the_registers[2];
	Utils::CacheFontTexture(self->FontTexture);
}
void __declspec(naked) __fastcall CTextObject_draw_Callback() {
	__asm {
		push eax;
		mov eax, saveRegistersJmpBack;
		mov[saveRegisters_jmpBack], eax;
		pop eax;
		jmp saveRegisters;
	saveRegistersJmpBack:
	}
	CTextObjectDrawThingIdek();
	//cout << "Func done" << endl;
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
		push - 01

		jmp[CTextObject_draw_jmpBack]
	}
}
#pragma endregion
#pragma region CBasePositionableObject Draw
int CBasePositionableObject_draw_jmpBack = 0;
void CBasePositionableObjectDrawThingIdek() {
	CBasePositionableObject* self = (CBasePositionableObject*)the_registers[2];
	//cout << "self: " << hex << self << endl;
	/*float lastAngle = self->Angle;
	float xd = 0.01 * (rand() % 100);
	self->SetAngle(lastAngle + (xd*2+.5));*/
}
void __declspec(naked) __fastcall CBasePositionableObject_draw_Callback() {
	__asm {
		push eax;
		mov eax, saveRegistersJmpBack;
		mov[saveRegisters_jmpBack], eax;
		pop eax;
		jmp saveRegisters;
	saveRegistersJmpBack:
	}
	CBasePositionableObjectDrawThingIdek();
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
		push esi
		mov esi, ecx

		jmp[CBasePositionableObject_draw_jmpBack]
	}
}
#pragma endregion
#pragma region Fps Cap Removal
int fpsCap_jmpBack = 0;
void __declspec(naked) __fastcall fpsCap_Callback() {
	__asm {
		jmp[fpsCap_jmpBack]
	}
}
#pragma endregion
#pragma region CBaseScreen Draw
#pragma region Registers
/*Register saving shit*/
int cbsd_the_registers[8];
int cbsd_saveRegisters_jmpBack = 0;
void __declspec(naked) cbsd_saveRegisters() {
	__asm {
		mov cbsd_the_registers[0 * 4], eax
		mov cbsd_the_registers[1 * 4], ebx
		mov cbsd_the_registers[2 * 4], ecx
		mov cbsd_the_registers[3 * 4], edx
		mov cbsd_the_registers[4 * 4], esi
		mov cbsd_the_registers[5 * 4], edi
		mov cbsd_the_registers[6 * 4], ebp
		mov cbsd_the_registers[7 * 4], esp

		jmp cbsd_saveRegisters_jmpBack;
	}
}
int cbsd_restoreRegisters_jmpBack = 0;
void __declspec(naked) cbsd_restoreRegisters() {
	__asm {
		mov eax, cbsd_the_registers[0 * 4]
		mov ebx, cbsd_the_registers[1 * 4]
		mov ecx, cbsd_the_registers[2 * 4]
		mov edx, cbsd_the_registers[3 * 4]
		mov esi, cbsd_the_registers[4 * 4]
		mov edi, cbsd_the_registers[5 * 4]
		mov ebp, cbsd_the_registers[6 * 4]
		mov esp, cbsd_the_registers[7 * 4]

		jmp cbsd_restoreRegisters_jmpBack
	}
}
#pragma endregion
CTextObject* nkhBrand;
string nkhString = "NKHook5";
void __fastcall CBaseScreenCallback() {
	//cout << "start" << endl;
	if (nkhBrand == nullptr) {
		if (Utils::getFontTexture() != nullptr) {
			nkhBrand = new CTextObject(nkhString);
		}
	}
	else {
		//cout << "Drawing..." << endl;
		nkhBrand->SetText(&nkhString);
		nkhBrand->SetScale(1, 1);
		nkhBrand->SetWH(100, 100);
		nkhBrand->SetXY(0, 256);
		nkhBrand->SetTexture(Utils::getFontTexture());
		nkhBrand->Draw(false);
		//cout << hex << nkhBrand << endl;
		//called = true;
		//cout << "Drawn" << endl;
		//system("pause");
	}
	//cout << "end" << endl;
}
int CBaseScreen_draw_drawChild_jmpBack = 0;
void __declspec(naked) __fastcall CBaseScreen_draw_drawChild_Callback() {
	__asm {
		push eax;
		mov eax, cbsd_saveRegistersJmpBack;
		mov[cbsd_saveRegisters_jmpBack], eax;
		pop eax;
		jmp cbsd_saveRegisters;
	cbsd_saveRegistersJmpBack:
	}
	CBaseScreenCallback();
	__asm {
		push eax;
		mov eax, cbsd_restoreRegistersJmpBack;
		mov[cbsd_restoreRegisters_jmpBack], eax;
		pop eax;
		jmp cbsd_restoreRegisters;
	cbsd_RestoreRegistersJmpBack:
	}
	__asm {
		mov ecx, [esi + 0x00000234]
		jmp[CBaseScreen_draw_drawChild_jmpBack]
	}
}
#pragma endregion

#pragma endregion

#pragma region Constructor
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
	cout << "Game Instance hook created" << endl;

	/*Keypress hook*/
	int keypressed = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "8B 7D 08 8B D9 81 FF 00 01 00 00 73 3A") - 5;
	if (MH_CreateHook((void*)keypressed, &keypressedCallback, reinterpret_cast<LPVOID*>(&keypressed_original)) == MH_OK) {
		if (MH_EnableHook((void*)keypressed) == MH_OK) {
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
	cout << "Bloon escaped hook created" << endl;

	/*Tower upgraded*/
	int upgradeTower = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "83 EC 44 53 8B 5D 08 8B") - 6;
	Utils::Detour32((void*)upgradeTower, &upgradeTowerCallback, 6);
	upgradeTowerJmpBack = upgradeTower + 6;
	cout << "Tower Upgraded hook created" << endl;

	/*game main hook (ignore)*/
	int gameMain = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8B EC 6A FF 68 CF 5F");
	int fpsCap = gameMain + 0xE0F;
	Utils::Detour32((void*)fpsCap, &fpsCap_Callback, 7);
	fpsCap_jmpBack = fpsCap + 7;
	cout << "Game Main hook created" << endl;


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


	/*CTextObject draw hook*/
	int CTextObject_draw = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "68 e9 fb ?? 00") - 5;//?? ?? ?? ?? ?? 68 e9 fb ?? 00
	Utils::Detour32((void*)CTextObject_draw, &CTextObject_draw_Callback, 5);
	CTextObject_draw_jmpBack = CTextObject_draw + 5;
	cout << "CTextObject draw hook created" << endl;

	/*CBasePositionableObject draw hook*/
	int CBasePositionableObject_draw = Utils::findPattern(Utils::getModuleBase() + 0x300000, Utils::getBaseModuleEnd(), "55 8b ec 56 8b f1 80 7e 0c 00 74 1a");
	Utils::Detour32((void*)CBasePositionableObject_draw, &CBasePositionableObject_draw_Callback, 6);
	CBasePositionableObject_draw_jmpBack = CBasePositionableObject_draw + 6;
	cout << "CBasePositionableObject draw hook created" << endl;

	/*CBaseScreen draw hook*/
	//nkhBrand = new CTextObject();
	int CBaseScreen_draw = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 8B F1 83 BE 40 01 00"); //56 8B F1 83 BE 40 01 00
	int CBaseScreen_draw_drawChild = CBaseScreen_draw + 0x40;
	Utils::Detour32((void*)CBaseScreen_draw_drawChild, &CBaseScreen_draw_drawChild_Callback, 6);
	CBaseScreen_draw_drawChild_jmpBack = CBaseScreen_draw_drawChild + 6;
	cout << "CBaseScreen draw hook created" << endl;
}
#pragma endregion