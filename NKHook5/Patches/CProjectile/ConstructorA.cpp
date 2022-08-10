#include "ConstructorA.h"

#include "../../Classes/CProjectile.h"
#include "../../ClassesEx/CProjectileExt.h"
#include "../../Signatures/Signature.h"

#include <Logging/Logger.h>
#include "../../Util/NewFramework.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CProjectile
        {
            using namespace Common::Logging;
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func = 0;
            Classes::CProjectile* __fastcall cb_hook(Classes::CProjectile* pProjectile, int pad, int param_1, int param_2, float param_3, float param_4) {
                return PLH::FnCast(o_func, &cb_hook)(pProjectile, pad, param_1, param_2, param_3, param_4);
            }

            auto ConstructorA::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CProjectile_CCTOR_A);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uintptr_t)address, (const uintptr_t)&cb_hook, &o_func);
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
        } // namespace CBloon
    }
}
