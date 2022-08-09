#include "Fire.h"

#include "../../Classes/CBaseTower.h"
#include "../../Classes/CWeapon.h"
#include "../../Classes/CBloonManager.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CWeapon
        {
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func;
            void __fastcall cb_hook(Classes::CWeapon* pWeapon, int pad, Classes::CBaseTower* pTower, Classes::CWeapon* param_2, Classes::CBloonManager* pBloonMgr) {
                
                PLH::FnCast(o_func, &cb_hook)(pWeapon, pad, pTower, param_2, pBloonMgr);
            }

            auto Fire::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CWeapon_Fire);
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
        } // namespace CWeapon
    }
}
