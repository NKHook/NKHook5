#include <Windows.h>
#include <string>
#include <iostream>
#include <Extensions/ExtensionManager.h>
#include "Extensions/StatusEffect/StatusDefinitionsExt.h"
#include "Patches/PatchManager.h"
#include "Signatures/Signature.h"

std::string* testModDir = nullptr;

auto initialize() -> int {
#ifdef _DEBUG
    printf("Press enter to launch NKH...\n");
    std::cin.get();
#endif
    std::cout << "Loading NKHook5..." << std::endl;

    wchar_t* cmdLine = GetCommandLineW();
    int argc;
    wchar_t** argv = CommandLineToArgvW(cmdLine, &argc);

    bool wantsModLaunch = false;
    wchar_t* wcModDir = nullptr;
    if (argv) {
        for (int i = 0; i < argc; i++) {
            if (wantsModLaunch) {
                wcModDir = argv[i];
                continue;
            }
            if (lstrcmpW(argv[i], L"--LaunchMod")) {
                wantsModLaunch = true;
                continue;
            }
            wprintf(L"Unknown arg at %d: %s\n", i, argv[i]);
        }
    }
    if (wcModDir) {
        std::wstring modWStr(wcModDir);
        testModDir = new std::string(modWStr.begin(), modWStr.end());
        printf("Launching mod: %s\n", testModDir->c_str());
    }

    printf("Searching signatures...\n");
    NKHook5::Signatures::FindAll();
    printf("Search complete! (Please report any search issues!!!)\n");

    printf("Loading Extensions...\n");
    Common::Extensions::ExtensionManager::AddAll();
    Common::Extensions::ExtensionManager::AddExtension(new NKHook5::Extensions::StatusEffect::StatusDefinitionsExt());
    printf("All extensions loaded!\n");

    std::cout << "Loading all patches..." << std::endl;
    NKHook5::Patches::PatchManager::ApplyAll();
    std::cout << "All patches loaded!" << std::endl;

    std::cout << "Loaded NKHook5!" << std::endl;
#ifdef _DEBUG
    printf("Press enter to boot game...\n");
    std::cin.get();
#endif

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