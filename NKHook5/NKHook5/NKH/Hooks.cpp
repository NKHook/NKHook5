#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "BloonSDK.h"

using namespace std;
void (__thiscall* FlagToString)(CFlagStringConvertor* conv, string buffer, uint64_t flag);
//FlagToString flagToStringOriginal;

void __fastcall flagToStringCallback(CFlagStringConvertor* conv, string buffer, uint64_t flag) {
    cout << "PRE CALL -------------" << endl;
    /*cout << "This: " << hex << conv << endl;
    cout << "Buffer: " << hex << buffer << endl;
    cout << "Flag: " << hex << flag << endl;*/
    /*cout << "Param1: " << hex << param_1 << endl;
    cout << "Param2: " << hex << param_2 << endl;
    cout << "Param3: " << hex << param_3 << endl;
    cout << "Param4: " << hex << param_4 << endl;*/
    FlagToString(conv, buffer, flag);
    cout << "POST CALL -------------" << endl;
    cout << "This: " << hex << conv << endl;
    cout << "Buffer: " << hex << buffer << endl;
    cout << "Flag: " << hex << flag << endl;
    /*cout << "Param1: " << hex << param_1 << endl;
    cout << "Param2: " << hex << param_2 << endl;
    cout << "Param3: " << hex << param_3 << endl;
    cout << "Param4: " << hex << param_4 << endl;*/
    cout << "END -------------" << endl;
}

Hooks::Hooks()
{
    if (MH_Initialize() == MH_OK) {
        int flagToString = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 ff 75 0C C7 45 FC 00 00 00 00 E8 E9") - 6;
        cout << "FlagToString:" << hex << flagToString << endl;
        if (MH_CreateHook((LPVOID)flagToString, flagToStringCallback, reinterpret_cast<LPVOID*>(&FlagToString)) == MH_OK) {
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
