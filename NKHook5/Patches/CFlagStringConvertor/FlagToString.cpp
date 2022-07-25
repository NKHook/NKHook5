#include "FlagToString.h"

#include <ghstl/string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            uint64_t o_func;
            ghstl::string* __fastcall cb_hook(class CFlagToStringConvertor* self, uint32_t pad, ghstl::string* result, uint32_t categoryId, uint64_t numericId) {
                ghstl::string* eaxResult =  PLH::FnCast(o_func, &cb_hook)(self, pad, result, categoryId, numericId);
                //printf("Numeric ID '%llx' was converted to '%s'\n", numericId, eaxResult->c_str());
                return eaxResult;
            }

            auto FlagToString::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 85");
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