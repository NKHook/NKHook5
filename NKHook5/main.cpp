#include <Windows.h>
#include <string>
#include <iostream>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>
#include "Utils.hpp"

#pragma comment(lib,"asmjit.lib")
#pragma comment(lib,"capstone.lib")
#pragma comment(lib,"PolyHook_2.lib")
#pragma comment(lib,"Zydis.lib")
#pragma comment(lib,"Zycore.lib")

uint64_t o_gamealloc = 0;
void* __fastcall cb_gamealloc(void* gameInstance) {
    std::cout << "Gameinstance created: " << gameInstance << std::endl;
    return PLH::FnCast(o_gamealloc, &cb_gamealloc)(gameInstance);
}

auto initialize() -> int {
    std::cout << "Loading NKHook5..." << std::endl;

    std::cout << "Hooking game constructor..." << std::endl;
    const uintptr_t p_gamealloc = Utils::findPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 51 56 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 ?? 75 ?? E8 ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 86 ?? ?? ?? ?? ?? ?? ?? ?? ?? 86 ?? ?? ?? ?? ?? ?? ?? ?? ?? 86 ?? ?? ?? ?? ?? ?? ?? ?? ?? 86 ?? ?? ?? ?? ?? ?? ?? ?? ?? 86");
    std::cout << "Found patch address " << std::hex << p_gamealloc << std::endl;
    if(p_gamealloc) {
        PLH::CapstoneDisassembler dis(PLH::Mode::x86);
        std::cout << "Found patch address " << std::hex << p_gamealloc << std::endl;
        PLH::x86Detour detour(p_gamealloc, (const uintptr_t)&cb_gamealloc, &o_gamealloc, dis);
        std::cout << "Found patch address " << std::hex << p_gamealloc << std::endl;
        if(detour.hook()) {
            std::cout << "PASS: gamealloc hook success, patched at: " << std::hex << p_gamealloc << std::endl;
        }
        else {
            std::cout << "FAIL: Could not hook gamealloc" << std::endl;
        }
    }
    else {
        std::cout << "FATAL FAILURE: Could not find gamealloc!" << std::endl;
    }


    std::cout << "Loaded NKHook5!" << std::endl;

    LoadLibraryA("Managed.dll");

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