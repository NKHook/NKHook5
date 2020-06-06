#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "BloonSDK.h"

using namespace std;
typedef void* (__fastcall* FlagToString)(CFlagStringConvertor* conv, uint64_t flag, int param_2, int param_3, int param_4, int param_5);
FlagToString flagToStringOriginal;

FlagToString flagToStringCallback(CFlagStringConvertor* conv, uint64_t flag, int param_2, int param_3, int param_4, int param_5) {
    cout << "PRE CALL -------------" << endl;
    cout << "This: " << hex << conv << endl;
    cout << "Flag: " << hex << param_2 << endl;
    cout << "Flag: " << hex << param_3 << endl;
    void* ret = flagToStringOriginal(conv, flag, param_2, param_3, param_4, param_5);
    cout << "POST CALL -------------" << endl;
    cout << "This: " << hex << conv << endl;
    cout << "Flag: " << hex << param_2 << endl;
    cout << "Flag: " << hex << param_3 << endl;
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
