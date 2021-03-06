#include <Windows.h>
#include "Entry.h"

void Initialize()
{
    NKHook5::Managed::Entry::Main();
}

#pragma unmanaged
extern "C" __declspec(dllexport) bool __stdcall DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            Initialize();
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}