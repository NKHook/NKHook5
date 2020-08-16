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
#include "NKH/SDK/CBaseTower.h"
#include "NKH/SDK/CBaseScreen.h"
#include "NKH/SDK/SigResults.h"



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

    /*CBasePositionableObject* cbpo = new CBasePositionableObject();
    cout << hex << "CBPO: " << cbpo << endl;
    CRenderableTextureObject* crto = new CRenderableTextureObject();
    cout << hex << "CRTO: " << crto << endl;
    CTextObject* cto = new CTextObject(new Vector2{ 0,256 }, new string("NKHook5"));
    cout << hex << "CTO: " << cto << endl;*/
    /*CBaseScreen* cbs = new CBaseScreen(new string("NKHScreen"));
    cout << hex << "CBS: " << cbs << endl;
    cbs->SetupPointers((CBaseScreen*)Utils::getGame()->CScreenManager);
    cout << "CBS SetupPtrs" << endl;*/
    /*cbs->Init();
    cout << "CBS Init" << endl;*/

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
                << "- help: show the help menu" << endl
                << "- reload: reload all scripts" << endl
                << "- crash: crash the game" << endl;
        }
        else if (line == "reload") {
            Chai::reloadScripts();
        }
        else if (line == "crash") {
            *(int*)0 = 0;
        }
        else if (line == "spinny" || line == "teckst") {
            Hooks::spinBrand = !Hooks::spinBrand;
        }
        else if (line == "test") {
            string* InGame = new string("newshared");
            string* steam_icon = new string("steam_icon");
            void* result = GetSpriteInfoPtr(Utils::getGame()->CTextureLoader, InGame, steam_icon);
            cout << "EPIC: " << hex << result << endl;
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

