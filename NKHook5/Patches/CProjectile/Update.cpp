#include "Update.h"

#include "../../Classes/CProjectile.h"
#include "../../Signatures/Signature.h"

#define MAX_PROJECTILE_UPDATES 256

extern uint64_t currentFrame;

namespace NKHook5
{
    namespace Patches
    {
        namespace CProjectile
        {
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t updatesThisFrame = 0;
            static uint64_t lastFrame = 0;
            static uint64_t o_func = 0;
            void __fastcall cb_hook(Classes::CProjectile* pProjectile, int pad, float* pSGameTime) {
                if (lastFrame != currentFrame) {
                    lastFrame = currentFrame;
                    updatesThisFrame = 0;
                }
                if (updatesThisFrame > MAX_PROJECTILE_UPDATES) {
                    return;
                }
                updatesThisFrame++;
                PLH::FnCast(o_func, &cb_hook)(pProjectile, pad, pSGameTime);
            }

            auto Update::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CProjectile_Update);
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
