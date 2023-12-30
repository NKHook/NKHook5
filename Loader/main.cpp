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
    auto nkhModule = LoadLibraryA("NKHook5.dll");
	if(!nkhModule)
	{
		//Get the error message ID, if any.
		DWORD errorMessageID = ::GetLastError();

		std::cout << "GLE: " << std::hex << errorMessageID << std::endl;

		LPSTR messageBuffer = nullptr;

		//Ask Win32 to give us the string version of that message ID.
		//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		//Copy the error message into a std::string.
		std::string message(messageBuffer, size);

		std::cout << "Error: " << message << std::endl;

		MessageBoxA(nullptr, "Failed to load NKHook5.dll!", "Load Error", MB_OK);

		//Free the Win32's string's buffer.
		LocalFree(messageBuffer);
	}

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