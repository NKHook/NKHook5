// dllmain.cpp : Definisce il punto di ingresso per l'applicazione DLL.

#include "pch.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "NKH/Hooks.h"
#include "NKH/Patches/FlagHacker.h"
#include "NKH/Blue/Chai.h"
#include "Utils.h"


using namespace std;
void StartNKH(HMODULE hModule) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    cout << "NKH is injected! Lets get things rolling!" << endl;

    Hooks();
    FlagHacker();
    //FlagHacker::addHackedFlag(new string("HackMonkey"), 0x4001);
    //FlagHacker::addHackedFlag(new string("Gaming"), 0x4002);

    while (Utils::getGame() == nullptr) { Sleep(100); }
    while (Utils::getGame()->CGameSystemPointers == nullptr) { Sleep(100); }

    Chai::startChai();
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

