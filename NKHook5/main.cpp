#include <Windows.h>
#include <string>
#include <iostream>
#include "Extensions/ExtensionManager.h"
#include "Patches/PatchManager.h"
#include "Signatures/Signature.h"

auto initialize() -> int {
    std::cout << "Loading NKHook5..." << std::endl;

    printf("Searching signatures...\n");
    NKHook5::Signatures::FindAll();
    printf("Search complete! (Please report any search issues!!!)\n");

    printf("Loading Extensions...\n");
    NKHook5::Extensions::ExtensionManager::AddAll();
    printf("All extensions loaded!\n");

    std::cout << "Loading all patches..." << std::endl;
    NKHook5::Patches::PatchManager::ApplyAll();
    std::cout << "All patches loaded!" << std::endl;

    std::cout << "Loaded NKHook5!" << std::endl;
    printf("Press enter to boot game...\n");
    std::cin.get();

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