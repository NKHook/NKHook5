#include <Windows.h>
#include <string>
#include <iostream>
#include <shlobj_core.h>

#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

HMODULE winINet;
int(__stdcall* InternetGetConnectedState_orig)(int,int);

extern "C" __declspec(dllexport) int __stdcall InternetGetConnectedState(int lpdwFlags, int dwReserved) {
    #pragma EXPORT
    int result = InternetGetConnectedState_orig(lpdwFlags, dwReserved);
    return result;
}

auto initialize() -> int {
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    std::cout << "Loading original WinINet.dll..." << std::endl;
    char syswowPath[MAX_PATH];
    SHGetFolderPathA(nullptr, CSIDL_SYSTEMX86, nullptr, SHGFP_TYPE_CURRENT, syswowPath);
    std::string syswowStr(syswowPath);
    std::string wininetPath = syswowStr + "\\wininet.dll";
    std::cout << "WinINet: " + wininetPath << std::endl;
    winINet = LoadLibraryA(wininetPath.c_str());
    InternetGetConnectedState_orig = (int(__stdcall*)(int,int))GetProcAddress(winINet, "InternetGetConnectedState");
    std::cout << "WinINet loaded" << std::endl;

    std::cout << "Launching NKHook5.dll..." << std::endl;
    LoadLibraryA("NKHook5.dll");

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