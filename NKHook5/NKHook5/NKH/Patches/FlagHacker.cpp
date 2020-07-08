#include "pch.h"
#include "FlagHacker.h"
#include "../../Utils.h"
#include <vector>



struct Flag {
public:
    FlagType type;
    string* name;
    long flag;
};

vector<Flag*> flags;


/*
Register storing shit to avoid crashing
*/
int registers[9];
int esPre = 0;

/*
String to flag hackerinos
*/

Flag* s2f_currentFlag = nullptr;
int pre_s2f_JmpBack = 0;
void __cdecl checkStrings(void* factory_cftsc, char* type) {
    bool foundHacked = false;
    for (int i = 0; i < flags.size(); i++) {
        if (strcmp(type, flags[i]->name->c_str()) == 0) {
            s2f_currentFlag = flags[i];
            foundHacked = true;
            cout << "Found hacked type" << endl;
        }
    }
    if (!foundHacked) {
        s2f_currentFlag = nullptr;
    }
}

long long __declspec(naked) __cdecl pre_stringToFlagDetour(void* factory_cftsc, char* type) {
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
    checkStrings(factory_cftsc, type);
    __asm {
        mov eax, registers[0 * 4]
        mov ebx, registers[1 * 4]
        mov ecx, registers[2 * 4]
        mov edx, registers[3 * 4]
        mov esi, registers[4 * 4]
        mov edi, registers[5 * 4]
        mov ebp, registers[6 * 4]
        mov esp, registers[7 * 4]

        jmp pre_s2f_JmpBack
    }
}

void __cdecl setHackedFlag() {
    if (s2f_currentFlag != nullptr) {
        registers[0] = s2f_currentFlag->flag;
        cout << "Type hacked" << endl;
    }
}
long long __declspec(naked) __cdecl post_stringToFlagDetour() {
    __asm {
        mov registers[0 * 4], eax
        mov registers[1 * 4], ebx
        mov registers[2 * 4], ecx
        mov registers[3 * 4], edx
        mov registers[4 * 4], esi
        mov registers[5 * 4], edi
        mov registers[6 * 4], ebp
        mov registers[7 * 4], esp
    }
    setHackedFlag();
    __asm {
        mov eax, registers[0 * 4]
        mov ebx, registers[1 * 4]
        mov ecx, registers[2 * 4]
        mov edx, registers[3 * 4]
        mov esi, registers[4 * 4]
        mov edi, registers[5 * 4]
        mov ebp, registers[6 * 4]
        mov esp, registers[7 * 4]

        mov esp, ebp
        pop ebp
        ret 0x0008

        jmp pre_s2f_JmpBack
    }
}

/*
Flag to String hackerinos
*/

Flag* f2s_currentFlag = nullptr;
int pre_f2s_JmpBack = 0;
int post_f2s_JmpBack = 0;

int pre_f2s_registers[9];
int post_f2s_registers[9];

void __cdecl checkTypes(long* flag) {

    long* eax_actualFlag_l = (long*)(((int)flag)-0x18);
    long* eax_actualFlag_h = (long*)(((int)flag)+0x30);
    int* ebx_actualFlag = (int*)(&pre_f2s_registers[1]);
    long* ebp_actualFlag = (long*)(((int)pre_f2s_registers[6]) + 0x10);
    long* esp_actualFlag = (long*)(((int)esPre)+0xC);


    /*cout << "eax_actualFlag_l: " << hex << *eax_actualFlag_l << endl;
    cout << "eax_actualFlag_h: " << hex << *eax_actualFlag_h << endl;
    cout << "ebx_actualFlag: " << hex << *ebx_actualFlag << endl;
    cout << "esp_actualFlag: " << hex << *esp_actualFlag << endl;
    cout << "ebp_actualFlag: " << hex << *ebp_actualFlag << endl;*/

    bool foundHacked = false;
    for (int i = 0; i < flags.size(); i++) {
        if (*eax_actualFlag_l == flags[i]->flag) {
            foundHacked = true;
            *eax_actualFlag_l = 0;
            f2s_currentFlag = flags[i];
        }
        if (*eax_actualFlag_h == flags[i]->flag) {
            foundHacked = true;
            *eax_actualFlag_h = 0;
            f2s_currentFlag = flags[i];
        }
        if (*esp_actualFlag == flags[i]->flag) {
            foundHacked = true;
            *esp_actualFlag = 0;
            f2s_currentFlag = flags[i];
        }
        if (*ebp_actualFlag == flags[i]->flag) {
            foundHacked = true;
            *ebp_actualFlag = 0;
            f2s_currentFlag = flags[i];
        }
        if (*ebx_actualFlag == flags[i]->flag) {
            foundHacked = true;
            *ebx_actualFlag = 0;
            f2s_currentFlag = flags[i];
        }
    }
    if (!foundHacked) {
        f2s_currentFlag = nullptr;
    }
}

long long __declspec(naked) __cdecl pre_flagToStringDetour(long* flag) {
    __asm {
        mov esPre, esp

        push ebp
        mov ebp, esp
        sub esp, 0x08

        mov pre_f2s_registers[0 * 4], eax
        mov pre_f2s_registers[1 * 4], ebx
        mov pre_f2s_registers[2 * 4], ecx
        mov pre_f2s_registers[3 * 4], edx
        mov pre_f2s_registers[4 * 4], esi
        mov pre_f2s_registers[5 * 4], edi
        mov pre_f2s_registers[6 * 4], ebp
        mov pre_f2s_registers[7 * 4], esp
    }
    checkTypes(flag);
    __asm {
        mov eax, pre_f2s_registers[0 * 4]
        mov ebx, pre_f2s_registers[1 * 4]
        mov ecx, pre_f2s_registers[2 * 4]
        mov edx, pre_f2s_registers[3 * 4]
        mov esi, pre_f2s_registers[4 * 4]
        mov edi, pre_f2s_registers[5 * 4]
        mov ebp, pre_f2s_registers[6 * 4]
        mov esp, pre_f2s_registers[7 * 4]

        jmp pre_f2s_JmpBack
    }
}

const char* hackedTypeCharPtr;
string hackedTypeStr;
string invalid = string("INVALID");
void __declspec(naked) __cdecl setHackedType() {
    if (f2s_currentFlag != nullptr) {
        cout << "Current flag is not null, hacking..." << endl;
        hackedTypeStr = *f2s_currentFlag->name;
        cout << "Hacked type: " << hackedTypeStr << endl;
        hackedTypeCharPtr = hackedTypeStr.c_str();
        __asm {
            mov eax, post_f2s_registers[0 * 4]
            mov ebx, post_f2s_registers[1 * 4]
            mov ecx, post_f2s_registers[2 * 4]
            mov edx, post_f2s_registers[3 * 4]
            mov esi, post_f2s_registers[4 * 4]
            mov edi, post_f2s_registers[5 * 4]
            mov ebp, post_f2s_registers[6 * 4]
            mov esp, post_f2s_registers[7 * 4]

            push hackedTypeCharPtr
            jmp post_f2s_JmpBack
        }
    }
    else {
        cout << "Current flag is null, skipping..." << endl;
        __asm {
            mov eax, post_f2s_registers[0 * 4]
            mov ebx, post_f2s_registers[1 * 4]
            mov ecx, post_f2s_registers[2 * 4]
            mov edx, post_f2s_registers[3 * 4]
            mov esi, post_f2s_registers[4 * 4]
            mov edi, post_f2s_registers[5 * 4]
            mov ebp, post_f2s_registers[6 * 4]
            mov esp, post_f2s_registers[7 * 4]

            push invalid
            jmp post_f2s_JmpBack
        }
    }
}

long long __declspec(naked) __cdecl post_flagToStringDetour() {
    __asm {
        mov post_f2s_registers[0 * 4], eax
        mov post_f2s_registers[1 * 4], ebx
        mov post_f2s_registers[2 * 4], ecx
        mov post_f2s_registers[3 * 4], edx
        mov post_f2s_registers[4 * 4], esi
        mov post_f2s_registers[5 * 4], edi
        mov post_f2s_registers[6 * 4], ebp
        mov post_f2s_registers[7 * 4], esp

        jmp setHackedType
    }
}

FlagHacker::FlagHacker() {
    /*
    StringToFlag detours
    */
    int stringToFlag = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "53 56 57 ff 75 08 e8 1f") - 6;
    pre_s2f_JmpBack = stringToFlag + 6;
    Utils::Detour32((void*)stringToFlag, &pre_stringToFlagDetour, 6);
    Utils::Detour32((void*)(stringToFlag+0xD2), &post_stringToFlagDetour, 6);
    Utils::Detour32((void*)(stringToFlag+0xDD), &post_stringToFlagDetour, 6);
    Utils::Detour32((void*)(stringToFlag+0xF5), &post_stringToFlagDetour, 6);

    /*
    FlagToString detours
    */
    int flagToString = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 ff 75 0c c7 45 FC 00 00 00 00 E8 E9") - 6;
    pre_f2s_JmpBack = flagToString + 6;
    Utils::Detour32((void*)flagToString, &pre_flagToStringDetour, 6);
    Utils::Detour32((void*)(flagToString + 0xB6), &post_flagToStringDetour, 5);
    post_f2s_JmpBack = flagToString + 0xB6 + 0x5;
}

void FlagHacker::addHackedFlag(FlagType type, string* name, long flag)
{
    Flag* sflag = new Flag();
    sflag->type = type;
    sflag->name = name;
    sflag->flag = flag;
    flags.push_back(sflag);
}
