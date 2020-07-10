#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "SDK/WinInput.h"

#include "Blue/Chai.h"

using namespace std;

typedef uint32_t uint;

typedef void (__fastcall* Keypressed)(WinInput* self, int param_1, char key);
Keypressed keypressed_original;
void __fastcall keypressedCallback(WinInput* self, int param_1, char key) {
	Chai::invokeKeyCallbacks(key);
	return keypressed_original(self, param_1, key);
}
typedef void(__cdecl* BloonEscaped)(void* theEvent, bool* param_2);
BloonEscaped bloonEscaped_original;
void __cdecl bloonEscapedCallback(void* theEvent, bool* param_2) {
	bloonEscaped_original(theEvent, param_2);
}

Hooks::Hooks()
{
	if (MH_Initialize() != MH_OK) {
		cout << "Failed to initialize minhook!" << endl;
		return;
	}

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
	/*
	int bloonEscaped = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "68 64 BF ?? ?? 64 A1") - 5;
	if (MH_CreateHook((void*)bloonEscaped, &bloonEscapedCallback, reinterpret_cast<LPVOID*>(&bloonEscaped_original))==MH_OK) {
		if (MH_EnableHook((void*)bloonEscaped)==MH_OK) {
			//cout << "Keypressed hook created!" << endl;
		}
		else {
			cout << "Failed to enable bloonEscaped hook" << endl;
		}
	}
	else {
		cout << "Failed to create bloonEscaped hook!" << endl;
	}
	*/
}