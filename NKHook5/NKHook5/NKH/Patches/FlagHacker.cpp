#include "pch.h"
#include "FlagHacker.h"
#include "../../Utils.h"
#include <vector>



struct Flag {
public:
    FlagType* type;
    string* name;
    long flag;
};

vector<Flag*> flags;

/*
String to flag hackerinos
*/
int pre_s2f_JmpBack = 0;
int pre_s2f_registers[9];
void __cdecl runCpp(void* factory_cftsc, char* type) {
    cout << "Detour" << endl;
    cout << "factory_cftsc: " << factory_cftsc << endl;
    cout << "type: " << type << endl;
    //system("pause");
}
long long __declspec(naked) __cdecl pre_stringToFlagDetour(void* factory_cftsc, char* type) {
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 0x0C

        mov pre_s2f_registers[0 * 4], eax
        mov pre_s2f_registers[1 * 4], ebx
        mov pre_s2f_registers[2 * 4], ecx
        mov pre_s2f_registers[3 * 4], edx
        mov pre_s2f_registers[4 * 4], esi
        mov pre_s2f_registers[5 * 4], edi
        mov pre_s2f_registers[6 * 4], ebp
        mov pre_s2f_registers[7 * 4], esp
    }
    runCpp(factory_cftsc, type);
    __asm {
        mov eax, pre_s2f_registers[0 * 4]
        mov ebx, pre_s2f_registers[1 * 4]
        mov ecx, pre_s2f_registers[2 * 4]
        mov edx, pre_s2f_registers[3 * 4]
        mov esi, pre_s2f_registers[4 * 4]
        mov edi, pre_s2f_registers[5 * 4]
        mov ebp, pre_s2f_registers[6 * 4]
        mov esp, pre_s2f_registers[7 * 4]
        jmp pre_s2f_JmpBack
    }
}

CFlagStringConvertor* TowerCFSC;

FlagHacker::FlagHacker() {
    int stringToFlag = Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "0c 53 56 57 ff 75 08 e8 1f") - 5;
    pre_s2f_JmpBack = stringToFlag + 6;
    Utils::Detour32((void*)stringToFlag, &pre_stringToFlagDetour, 6);
    CBloonsTD5Game* game = Utils::getGame();
    TowerCFSC = &(game->CGameSystemPointers->CTowerFactory->CFlagStringConvertor);
}

void FlagHacker::addHackedFlag(FlagType* type, string* name, long flag)
{
    Flag* sflag = new Flag();
    sflag->type = type;
    sflag->name = name;
    sflag->flag = flag;
    flags.push_back(sflag);
}
