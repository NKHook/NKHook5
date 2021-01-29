#include <Windows.h>
#include <string>
#include <iostream>

extern "C" __declspec(dllexport) bool InternetGetConnectedState(LPDWORD lpdwFlags, DWORD   dwReserved) {
    return true;
}

auto initialize() -> int {
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    std::cout << "Haha doing shit before game go brrrr" << std::endl;
    Sleep(1000);
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