#include "GetText.h"

#include <ghstl/string>
#include <string>
#include "../../Classes/CLoc.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            uint64_t o_func;
            void* __fastcall cb_hook(Classes::CLoc* pCLoc, uint32_t pad, ghstl::string* result, Classes::Texts textId, Classes::SLangDef* language) {
                void* res = PLH::FnCast(o_func, &cb_hook)(pCLoc, pad, result, textId, language);
                printf("ID: %x Result: %s\n", textId, result->c_str());
                return res;
            }

            auto GetText::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F9 8B ?? ?? 8B ?? ?? 8B ?? ?? ?? 75 ?? ?? 45");
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
                    if(detour->hook())
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