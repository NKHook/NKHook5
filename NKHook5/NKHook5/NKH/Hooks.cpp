#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "BloonsSDK.h"

using namespace std;
typedef void* (__stdcall* FlagToString)(void* puParm1, int uParm2, int uParm3, int uParm4);
FlagToString flagToStringOriginal;

__declspec(dllexport) void* __stdcall flagToStringCallback(void* puParm1, int uParm2, int uParm3, int uParm4) {
    cout << "PRE CALL -------------" << endl;
    cout << "This: " << hex << puParm1 << endl;
    cout << "FlagA: " << hex << uParm2 << endl;
    cout << "FlagB: " << hex << uParm3 << endl;
    cout << "FlagC: " << hex << uParm4 << endl;
    void* ret = flagToStringOriginal(puParm1, uParm2, uParm3, uParm4);
    cout << "POST CALL -------------" << endl;
    cout << "This: " << hex << puParm1 << endl;
    cout << "FlagA: " << hex << uParm2 << endl;
    cout << "FlagB: " << hex << uParm3 << endl;
    cout << "FlagC: " << hex << uParm4 << endl;
    cout << "END -------------" << endl;
    return ret;
}

Hooks::Hooks()
{
    if (MH_Initialize() == MH_OK) {
        int flagToString = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 ff 75 0C C7 45 FC 00 00 00 00 E8 E9") - 6;
        cout << "FlagToString:" << hex << flagToString << endl;
        if (MH_CreateHook((LPVOID)flagToString, &flagToStringCallback, (LPVOID*)&flagToStringOriginal) == MH_OK) {
            cout << "Hook created!" << endl;
            if (MH_EnableHook((LPVOID)flagToString) == MH_OK) {
                cout << "Hook enabled!" << endl;
            }
            else {
                cout << "Failed to enable hook!" << endl;
            }
        }
        else {
            cout << "Failed!";
        }
    }
    else {
        cout << "MinHook failed to load!";
    }

}