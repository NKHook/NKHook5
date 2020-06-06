#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "BloonsSDK.h"

using namespace std;
typedef void* (__thiscall* FlagToString)(CFlagStringConvertor* conv);
FlagToString flagToStringOriginal;

__declspec(dllexport) void* __fastcall flagToStringCallback(CFlagStringConvertor* conv) {
    cout << "PRE CALL -------------" << endl;
    cout << "This: " << hex << conv << endl;
    /*cout << "FlagA: " << hex << flagA << endl;
    cout << "FlagB: " << hex << flagB << endl;
    cout << "FlagC: " << hex << flagC << endl;*/
    void* ret = flagToStringOriginal(conv);
    cout << "POST CALL -------------" << endl;
    cout << "This: " << hex << conv << endl;
    /*cout << "FlagA: " << hex << flagA << endl;
    cout << "FlagB: " << hex << flagB << endl;
    cout << "FlagC: " << hex << flagC << endl;*/
    cout << "END -------------" << endl;
    while(1){}
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