#include <Windows.h>
#include <string>
#include <iostream>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>
#include "Utils.hpp"

uint64_t o_winmain = 0;
void __stdcall cb_winmain(HINSTANCE param_1, int param_2, int** param_3) {
    std::cout << "Hello from main!" << std::endl;
    return PLH::FnCast(o_winmain, &cb_winmain)(param_1, param_2, param_3);
}

auto initialize() -> int {
    std::cout << "Loading NKHook5..." << std::endl;

    std::cout << "Hooking game initialization..." << std::endl;
    const uintptr_t p_winmain = Utils::findPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? ?? 65 ?? 8B ?? ?? 8D ?? ?? ?? ?? ?? 8B");
    std::cout << "Found patch address " << std::hex << p_winmain << std::endl;
    if(p_winmain) {
        PLH::CapstoneDisassembler dis(PLH::Mode::x86);
        std::cout << "Found patch address " << std::hex << p_winmain << std::endl;
        PLH::x86Detour detour(p_winmain, (const uintptr_t)&cb_winmain, &o_winmain, dis);
        std::cout << "Found patch address " << std::hex << p_winmain << std::endl;
        if(detour.hook()) {
            std::cout << "PASS: Winmain hook success, patched at: " << std::hex << p_winmain << std::endl;
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