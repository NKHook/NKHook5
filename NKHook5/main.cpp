#include <Windows.h>
#include <string>
#include <iostream>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>
#include "Utils.hpp"

void __stdcall cb_winmain(HINSTANCE param_1, int param_2, int** param_3) {

}
void(__stdcall* o_winmain)(HINSTANCE param_1, int param_2, int** param_3);

auto initialize() -> int {
    std::cout << "Loading NKHook5..." << std::endl;

    std::cout << "Hooking game initialization..." << std::endl;
    int winmain = Utils::findPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? ?? 65 ?? 8B ?? ?? 8D ?? ?? ?? ?? ?? 8B");
    if(winmain) {
        PLH::CapstoneDisassembler dis(PLH::Mode::x86);
        PLH::x86Detour detour((const uint64_t)&winmain, (const uint64_t)&cb_winmain, (uint64_t*)&o_winmain, dis);
        if(detour.hook()) {
            std::cout << "PASS: Winmain hook success" << std::endl;
        }
        else {
            std::cout << "FAIL: Count not hook winmain" << std::endl;
        }
    }
    else {
        std::cout << "FATAL FAILURE: Could not find winmain!" << std::endl;
    }


    std::cout << "Loaded NKHook5!" << std::endl;
    return 0;
}


extern "C" __declspec(dllexport) bool __stdcall DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            initialize();
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}