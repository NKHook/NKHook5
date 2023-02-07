#include "GetTowerInfo.h"

#include <ghstl/string>
#include "../../Classes/CTowerFactory.h"
#include "../../Classes/STowerInfo.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CTowerFactory
        {
            using namespace Signatures;

            static uint64_t o_func;
            Classes::STowerInfo* __fastcall cb_hook(Classes::CTowerFactory* self, void* pad, uint64_t flagId)
            {
                return PLH::FnCast(o_func, &cb_hook)(self, pad, flagId);
            }

            auto GetTowerInfo::Apply() -> bool
            {
                void* address = Signatures::GetAddressOf(Sigs::CTowerFactory_GetTowerInfo);
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