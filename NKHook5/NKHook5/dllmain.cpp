// dllmain.cpp : Definisce il punto di ingresso per l'applicazione DLL.

#include "pch.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "NKH/Hooks.h"
#include "NKH/Patches/FlagHacker.h"
#include "NKH/Blue/Chai.h"
#include "Utils.h"
#include "NKH/SDK/CGameSystemPointers.h"
#include "NKH/SDK/CTowerManager.h"
#include "NKH/SDK/CTextObject.h"
#include "NKH/SDK/CBasePositionableObject.h"



using namespace std;
void StartNKH(HMODULE hModule) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);

    cout << "NKH is injected! Lets get things rolling!" << endl;

    //Epic window title
    SetWindowTextA(GetConsoleWindow(), "NKHook5 - Console");

    Hooks();
    FlagHacker();
    //FlagHacker::addHackedFlag(new string("HackMonkey"), 0x4001);
    //FlagHacker::addHackedFlag(new string("Gaming"), 0x4002);

    while (Utils::getGame() == nullptr) { Sleep(100); }
    //cout << "Get game returned: " << Utils::getGame() << endl;
    while (Utils::getGame()->CGameSystemPointers == nullptr) { Sleep(100); }

    Chai::startChai();

    while (Utils::getFontTexture() == nullptr) { Sleep(100); }

    CBasePositionableObject* cbpo = new CBasePositionableObject();
    cout << hex << "CBPO: " << cbpo << endl;
    CTextObject* cto = new CTextObject("NKHook5");
    //cto->SetText(new basic_string<char>("Retard"));
    cout << hex << "CTO: " << cto << endl;

    //renderCTO(cto);

    /*cout << "String size: " << sizeof(string) << endl;
    cout << "basic_string size: " << sizeof(basic_string<char>) << endl;*/

    cout << "using main thread for inputs" << endl;
    string line;
    while (true) {
        getline(cin, line);
        if (line == "help") {
            //cout << "Commands aren't supported yet." << endl
            cout << "NKH commands:" << endl
                << "- help" << endl
                << "- reload" << endl;
        }
        else if (line == "reload") {
            Chai::reloadScripts();
        }
        else if (line == "kill") {
            *(int*)0 = 0;
        }
        else {
            if (!Chai::invokeConsoleInputCallbacks(line)) {
                cout << "Unknown command" << endl;
                //cout << hex << Utils::getGame()->CGameSystemPointers->CTowerManager->getTowerCount() << endl;
            }
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

