#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "BloonsSDK.h"

using namespace std;

typedef void (__thiscall* Keypressed)(WinInput*, char, int);
Keypressed keypressed_original;
void __fastcall keypressedCallback(WinInput* self, char key, int UNKNOWN) {
	cout << hex << self << endl;
	cout << key << endl;
	cout << hex << UNKNOWN << endl;
	system("pause");
	keypressed_original(self, key, UNKNOWN);
}

Hooks::Hooks()
{
	if (MH_Initialize() == MH_OK) {
		int keypressed = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "8B 7D 08 8B D9 81 FF 00 01 00 00 73 3A") - 5;
		if (MH_CreateHook((void*)keypressed, &keypressedCallback, reinterpret_cast<LPVOID*>(&keypressed_original))==MH_OK) {
			if (MH_EnableHook((void*)keypressed)==MH_OK) {
				cout << "Keypressed hook created!" << endl;
			}
			else {
				cout << "Failed to enable keypressed hook" << endl;
			}
		}
		else {
			cout << "Failed to create keypressed hook!" << endl;
		}
	}
	else {
		cout << "FATAL: Failed to initialize minhook!" << endl;
	}

}