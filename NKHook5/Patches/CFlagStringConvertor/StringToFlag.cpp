#include "StringToFlag.h"

#include <ghstl/string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            static uint64_t o_func;
            uint64_t __fastcall cb_hook(class CFlagStringConvertor* self, int pad, int categoryId, ghstl::string* textId) {
                uint64_t eaxResult =  PLH::FnCast(o_func, &cb_hook)(self, pad, categoryId, textId);
                //printf("Numeric ID '%llx' was converted to '%s'\n", numericId, eaxResult->c_str());
                return eaxResult;
            }

            auto StringToFlag::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 83 EC ?? 53 56 57 ?? ?? ?? E8");
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