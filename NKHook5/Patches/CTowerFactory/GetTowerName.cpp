#include "GetTowerName.h"

#include <ghstl/string>
#include "../../Classes/CTowerFactory.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CTowerFactory
        {
            using namespace Signatures;

            static uint64_t o_func;
            void* __fastcall cb_hook(Classes::CTowerFactory* self, void* pad, std::string* out_name, uint64_t flagId)
            {
                return PLH::FnCast(o_func, &cb_hook)(self, pad, out_name, flagId);
            }

            auto GetTowerName::Apply() -> bool
            {
                void* address = Signatures::GetAddressOf(Sigs::CTowerFactory_GetTowerName);
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