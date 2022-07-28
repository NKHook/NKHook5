#include "StringToFlag.h"

#include "../../Signatures/Signature.h"
#include <ghstl/string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            using namespace Signatures;

            static uint64_t o_func;
            uint64_t __fastcall cb_hook(class CFlagStringConvertor* self, int pad, int categoryId, ghstl::string* textId) {
                uint64_t eaxResult =  PLH::FnCast(o_func, &cb_hook)(self, pad, categoryId, textId);
                //printf("Numeric ID '%llx' was converted to '%s'\n", numericId, eaxResult->c_str());
                return eaxResult;
            }

            auto StringToFlag::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_StringToFlag);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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