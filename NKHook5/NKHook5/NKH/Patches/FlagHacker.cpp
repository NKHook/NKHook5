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


/*
String to flag hackerinos
*/

Flag* s2f_current;
int pre_s2f_JmpBack = 0;
void __cdecl checkTypes(void* factory_cftsc, char* type) {
    bool foundHacked = false;
    for (int i = 0; i < flags.size(); i++) {
        if (strcmp(type, flags[i]->name->c_str()) == 0) {
            s2f_current = flags[i];
            foundHacked = true;
            cout << "Found hacked type" << endl;
        }
    }
    if (!foundHacked) {
        s2f_current = nullptr;
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
    checkTypes(factory_cftsc, type);
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

void __cdecl setHackedType() {
    if (s2f_current != nullptr) {
        registers[0] = s2f_current->flag;
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
    setHackedType();
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
    setHackedType();
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

CFlagStringConvertor* TowerCFSC;

FlagHacker::FlagHacker() {
    /*
    StringToFlag detours
    */
    int stringToFlag = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "0c 53 56 57 ff 75 08 e8 1f") - 5;
    pre_s2f_JmpBack = stringToFlag + 6;
    Utils::Detour32((void*)stringToFlag, &pre_stringToFlagDetour, 6);
    Utils::Detour32((void*)(stringToFlag+0xDD), &post_A_stringToFlagDetour, 6);
    Utils::Detour32((void*)(stringToFlag+0xF5), &post_B_stringToFlagDetour, 6);
}

void FlagHacker::addHackedFlag(FlagType type, string* name, long flag)
{
    Flag* sflag = new Flag();
    sflag->type = type;
    sflag->name = name;
    sflag->flag = flag;
    flags.push_back(sflag);
}
