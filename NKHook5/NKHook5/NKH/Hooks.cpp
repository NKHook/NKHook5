#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>

using namespace std;

//typedef string (__thiscall* FlagToString)(void);

Hooks::Hooks()
{
    /*if (MH_Initialize() == MH_OK) {
        int result = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 ff 75 0C C7 45 FC 00 00 00 00 E8 E9") - 6;
        cout << "FlagToString:" << hex << result << endl;
        MH_CreateHook(result, )
    }
    else {
        cout << "MinHook failed to load!";
    }*/
    
}
