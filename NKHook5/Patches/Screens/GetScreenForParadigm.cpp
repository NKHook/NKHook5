#include "GetScreenForParadigm.h"

#include "../../Classes/CGameSystemPointers.h"
#include "../../Classes/CBloonsBaseScreen.h"
#include "../../Classes/CPopupScreenBase.h"
#include "../../Classes/DeviceType.h"
#include "../../Signatures/Signature.h"

#include <string>

namespace NKHook5
{
    namespace Patches
    {
        namespace Screens
        {
            using namespace Signatures;

            Classes::CBloonsBaseScreen* __cdecl ModdedScreenProxy(std::string& screenName, Classes::eDeviceType deviceType, Classes::CGameSystemPointers* pCGameSystemPointers) {
                printf("Finding screen \"%s\"", screenName.c_str());
                return nullptr;
            }

            uint32_t o_func;
            __declspec(naked) void __fastcall fGetScreenForParadigm(std::string& screenName, Classes::eDeviceType deviceType, Classes::CGameSystemPointers* pCGameSystemPointers) {
                CallProxy:
                __asm {
                    push esp
                    push edx
                    push ecx
                    call ModdedScreenProxy
                    pop ecx
                    pop edx
                    pop esp
                    test eax, eax
                    jnz Otherwise
                }
                GameCode:
                //Call o_func
                __asm {
                    jmp [o_func]
                }
                Otherwise:
                __asm {}
            }

            auto GetScreenForParadigm::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::Screens_GetScreenForParadigm);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&fGetScreenForParadigm, (uint64_t*)&o_func);
                    if (detour->hook())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
    }
}