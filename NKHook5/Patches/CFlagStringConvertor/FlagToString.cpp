#include "FlagToString.h"

#include "../../Classes/CFlagStringConvertor.h"
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
            ghstl::string* __fastcall cb_hook(Classes::CFlagStringConvertor* self, uint32_t pad, ghstl::string* result, uint32_t categoryId, uint64_t numericId) {
                ghstl::string* eaxResult =  PLH::FnCast(o_func, &cb_hook)(self, pad, result, categoryId, numericId);
                //printf("Numeric ID '%llx' was converted to '%s'\n", numericId, eaxResult->c_str());
                return eaxResult;
            }

            auto FlagToString::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_FlagToString);
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