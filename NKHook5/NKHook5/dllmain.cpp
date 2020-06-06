// dllmain.cpp : Definisce il punto di ingresso per l'applicazione DLL.

#include "pch.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "NKH/Hooks.h"


using namespace std;
void StartNKH(HMODULE hModule) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    cout << "NKH is injected! Lets get things rolling!" << endl;

    Hooks();

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartNKH, hModule, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

