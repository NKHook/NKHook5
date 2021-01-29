#include <Windows.h>
#include <string>
#include <iostream>


auto initialize() -> int {
    std::cout << "Loading NKHook5..." << std::endl;
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