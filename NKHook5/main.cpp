#include <Windows.h>
#include <string>
#include <iostream>

#include <Extensions/ExtensionManager.h>
#include <Logging/Logger.h>

#include "Extensions/StatusEffect/StatusDefinitionsExt.h"
#include "Patches/PatchManager.h"
#include "Signatures/Signature.h"

std::string* testModDir = nullptr;

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

auto initialize() -> int {
#ifdef _DEBUG
    Print(LogLevel::INFO, "Press enter to launch NKH...");
    std::cin.get();
#endif
    Print(LogLevel::INFO, "Loading NKHook5...");

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
        Print(LogLevel::INFO, "Launching mod: %s", testModDir->c_str());
    }

    Print(LogLevel::INFO, "Searching signatures...");
    NKHook5::Signatures::FindAll();
    Print(LogLevel::INFO, "Search complete! (Please report any search issues!!!)");

    Print(LogLevel::INFO, "Loading Extensions...");
    Common::Extensions::ExtensionManager::AddAll();
    Common::Extensions::ExtensionManager::AddExtension(new NKHook5::Extensions::StatusEffect::StatusDefinitionsExt());
    Print(LogLevel::INFO, "All extensions loaded!");

    Print(LogLevel::INFO, "Loading all patches...");
    NKHook5::Patches::PatchManager::ApplyAll();
    Print(LogLevel::INFO, "All patches loaded!");

    Print(LogLevel::INFO, "Loaded NKHook5!");
#ifdef _DEBUG
    Print(LogLevel::INFO, "Press enter to boot game...");
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