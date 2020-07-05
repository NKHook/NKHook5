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

Flag* currentFlag = nullptr;
int pre_s2f_JmpBack = 0;
void __cdecl checkStrings(void* factory_cftsc, char* type) {
    bool foundHacked = false;
    for (int i = 0; i < flags.size(); i++) {
        if (strcmp(type, flags[i]->name->c_str()) == 0) {
            currentFlag = flags[i];
            foundHacked = true;
            cout << "Found hacked type" << endl;
        }
    }
    if (!foundHacked) {
        currentFlag = nullptr;
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
    if (currentFlag != nullptr) {
        registers[0] = currentFlag->flag;
        cout << "Type hacked" << endl;
    }
}

long long __declspec(naked) __cdecl post_A_stringToFlagDetour() {
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
long long __declspec(naked) __cdecl post_B_stringToFlagDetour() {
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
int pre_f2s_JmpBack = 0;
int post_f2s_JmpBack = 0;

void __cdecl checkTypes(long* flag) {

    long* eax_actualFlag = (long*)(((int)flag)-0x18);
    long* esp_actualFlag = (long*)(((int)esPre)+0xC);

    cout << "eax_actualFlag: " << hex << *eax_actualFlag << endl;
    cout << "esp_actualFlag: " << hex << *esp_actualFlag << endl;

    bool foundHacked = false;
    for (int i = 0; i < flags.size(); i++) {
        if (*eax_actualFlag == flags[i]->flag) {
            currentFlag = flags[i];
            foundHacked = true;
            *eax_actualFlag = 0;
            //cout << "Found hacked flag (eax)" << endl;
        }
        if (*esp_actualFlag == flags[i]->flag) {
            currentFlag = flags[i];
            foundHacked = true;
            *esp_actualFlag = 0;
            //cout << "Found hacked flag (esp)" << endl;
        }
    }
    if (!foundHacked) {
        currentFlag = nullptr;
    }
}

long long __declspec(naked) __cdecl pre_flagToStringDetour(long* flag) {
    __asm {
        mov esPre, esp

        push ebp
        mov ebp, esp
        sub esp, 0x08

        mov registers[0 * 4], eax
        mov registers[1 * 4], ebx
        mov registers[2 * 4], ecx
        mov registers[3 * 4], edx
        mov registers[4 * 4], esi
        mov registers[5 * 4], edi
        mov registers[6 * 4], ebp
        mov registers[7 * 4], esp
    }
    checkTypes(flag);
    __asm {
        mov eax, registers[0 * 4]
        mov ebx, registers[1 * 4]
        mov ecx, registers[2 * 4]
        mov edx, registers[3 * 4]
        mov esi, registers[4 * 4]
        mov edi, registers[5 * 4]
        mov ebp, registers[6 * 4]
        mov esp, registers[7 * 4]

        jmp pre_f2s_JmpBack
    }
}

string hackedTypeStr;
string invalid = string("INVALID");
void __declspec(naked) __cdecl setHackedType() {
    if (currentFlag != nullptr) {
        cout << "Current flag is not null, hacking..." << endl;
        hackedTypeStr = *currentFlag->name;
        __asm {
            mov eax, registers[0 * 4]
            mov ebx, registers[1 * 4]
            mov ecx, registers[2 * 4]
            mov edx, registers[3 * 4]
            mov esi, registers[4 * 4]
            mov edi, registers[5 * 4]
            mov ebp, registers[6 * 4]
            mov esp, registers[7 * 4]

            push [hackedTypeStr+0x4]
            jmp post_f2s_JmpBack
        }
    }
    else {
        cout << "Current flag is null, skipping..." << endl;
        __asm {
            mov eax, registers[0 * 4]
            mov ebx, registers[1 * 4]
            mov ecx, registers[2 * 4]
            mov edx, registers[3 * 4]
            mov esi, registers[4 * 4]
            mov edi, registers[5 * 4]
            mov ebp, registers[6 * 4]
            mov esp, registers[7 * 4]

            push invalid
            jmp post_f2s_JmpBack
        }
    }
}

long long __declspec(naked) __cdecl post_flagToStringDetour() {
    __asm {
        mov registers[0 * 4], eax
        mov registers[1 * 4], ebx
        mov registers[2 * 4], ecx
        mov registers[3 * 4], edx
        mov registers[4 * 4], esi
        mov registers[5 * 4], edi
        mov registers[6 * 4], ebp
        mov registers[7 * 4], esp

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
    Utils::Detour32((void*)(stringToFlag+0xDD), &post_A_stringToFlagDetour, 6);
    Utils::Detour32((void*)(stringToFlag+0xF5), &post_B_stringToFlagDetour, 6);

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
