#pragma once
#include "pch.h"
#include "Hooks.h"
#include "../Utils.h"
#include <iostream>
#include <functional>

#include <MinHook.h>
#include "BloonsSDK.h"

using namespace std;
//typedef void* (__stdcall* FlagToString)(void* puParm1, int uParm2, int uParm3, int uParm4);
//FlagToString flagToStringOriginal;
//
//__declspec(naked) void __stdcall flagToStringCallback(void* puParm1, int uParm2, int uParm3, int uParm4) {
//    __asm {
//        push ebp
//        mov ebp, esp
//        sub esp, 0x8
//        push esi
//        push edi
//    }
//    cout << "PRE CALL -------------" << endl;
//    cout << "puParm1: " << hex << puParm1 << endl;
//    cout << "uParm2: " << hex << uParm2 << endl;
//    cout << "uParm3: " << hex << uParm3 << endl;
//    cout << "uParm4: " << hex << uParm4 << endl;
//    flagToStringOriginal(puParm1, uParm2, uParm3, uParm4);
//    cout << "POST CALL -------------" << endl;
//    cout << "puParm1: " << hex << puParm1 << endl;
//    cout << "uParm2: " << hex << uParm2 << endl;
//    cout << "uParm3: " << hex << uParm3 << endl;
//    cout << "uParm4: " << hex << uParm4 << endl;
//    //cout << "Ret: " << hex << ret << endl;
//    cout << "END -------------" << endl;
//    system("pause");
//    __asm {
//        pop edi
//        pop esi
//        mov esp, ebp
//        pop ebp
//        ret 0x10
//    }
//}


typedef long long (__cdecl* StringToFlag)(void* convertor, void* type);
StringToFlag stringToFlagOriginal;
//long stringToFlagCallback(void* convertor, string flag) {
//    cout << flag << endl;
//    return stringToFlagOriginal(convertor, flag);
//}

void __cdecl runCpp() {
    cout << "Detour" << endl;
}

int jmpBack = 0;
int registers[9];
CFlagStringConvertor* TowerCFSC;
long long __declspec(naked) __cdecl stringToFlagDetour(void* factory_cftsc, void* type) {
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 0x0C

        mov registers[0 * 4], eax
        mov registers[1 * 4], ebx
        mov registers[2 * 4], ecx
        mov registers[3 * 4], edx
        mov registers[4 * 4], esi
        mov registers[5 * 4], edi
        mov registers[6 * 4], ebp
        mov registers[7 * 4], esp
    }
    runCpp();
    __asm {

        mov eax, registers[0 * 4]
        mov ebx, registers[1 * 4]
        mov ecx, registers[2 * 4]
        mov edx, registers[3 * 4]
        mov esi, registers[4 * 4]
        mov edi, registers[5 * 4]
        mov ebp, registers[6 * 4]
        mov esp, registers[7 * 4]

        jmp jmpBack
    }
}
Hooks::Hooks()
{
    int stringToFlag = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "0c 53 56 57 ff 75 08 e8 1f") - 5;
    jmpBack = stringToFlag + 6;
    Utils::Detour32((void*)stringToFlag, &stringToFlagDetour, 6);
    CBloonsTD5Game* game = Utils::getGame();
    TowerCFSC = &(game->CGameSystemPointers->CTowerFactory->CFlagStringConvertor);
    /*
    if (MH_Initialize() == MH_OK) {
        int getTowerInfo = Utils::getModuleBase() + 0x174520; //Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8B EC 6A FF 68 ?8 1? ?? ?? ?? A1 00 00 00 00 50 83 EC 24 A1 34 B0 ?? 01 33 C5 89 45 F0 56 50 8D 45 F4 64 A3 00 00 00 00 8B F1 8B");
        cout << "GetTowerInfo: " << hex << getTowerInfo << endl;
        if (MH_CreateHook((LPVOID)getTowerInfo, &getTowerInfoCallback, (LPVOID*)&getTowerInfoOriginal) == MH_OK) {
            cout << "Hook created!" << endl;
            if (MH_EnableHook((LPVOID)getTowerInfo) == MH_OK) {
                cout << "Hook enabled!" << endl;
            }
        }
    }
    */
    /*if (MH_Initialize() == MH_OK) {
        int stringToFlag = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "0c 53 56 57 ff 75 08 e8 1f") - 5;
        cout << "StringToFlag:" << hex << stringToFlag << endl;
        if (MH_CreateHook((LPVOID)stringToFlag, &stringToFlagTrampoline, (LPVOID*)&stringToFlagOriginal) == MH_OK) {
            cout << "Hook created!" << endl;
            if (MH_EnableHook((LPVOID)stringToFlag) == MH_OK) {
                cout << "Hook enabled!" << endl;
            }
            else {
                cout << "Failed to enable hook!" << endl;
            }
        }
        else {
            cout << "Failed!";
        }
    }
    else {
        cout << "MinHook failed to load!";
    }*/

}