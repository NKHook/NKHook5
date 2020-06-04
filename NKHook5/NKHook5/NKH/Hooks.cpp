#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

using namespace std;
Hooks::Hooks()
{
    cout << "Size:" << hex << Utils::getBaseModuleSize() << endl;
    cout << "Beginning:" << hex << Utils::getModuleBase() << endl;
    cout << "End:" << hex << Utils::getBaseModuleEnd() << endl;
    int result = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 ff 75 0C C7 45 FC 00 00 00 00 E8 E9")-6;
    cout << "FlagToString:" << hex << result << endl;
}
