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
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);

    cout << "NKH is injected! Lets get things rolling!" << endl;

    Hooks();
    FlagHacker();
    //FlagHacker::addHackedFlag(new string("HackMonkey"), 0x4001);
    //FlagHacker::addHackedFlag(new string("Gaming"), 0x4002);

    while (Utils::getGame() == nullptr) { Sleep(100); }
    while (Utils::getGame()->CGameSystemPointers == nullptr) { Sleep(100); }

    Chai::startChai();

    cout << "using main thread for inputs" << endl;
    string line;
    while (true) {
        getline(cin, line);
        if (strcmp(line.c_str(), "help") == 0) {
            cout << "Commands aren't supported yet." << endl
                << "Existing commands:" << endl
                << "- help" << endl
                << "- reload" << endl;
        }
        else if (strcmp(line.c_str(), "reload") == 0) {
            Chai::reloadScripts();
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
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

