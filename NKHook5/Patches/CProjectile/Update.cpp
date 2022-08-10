#include "Update.h"

#include "../../Classes/CProjectile.h"
#include "../../ClassesEx/CProjectileExt.h"
#include "../../Signatures/Signature.h"

#include <Logging/Logger.h>

extern uint64_t currentFrame;
int32_t maxProjectileUpdates = 0x200;
int32_t maxProjectilesTotal = 0x400;

namespace NKHook5
{
    namespace Patches
    {
        namespace CProjectile
        {
            using namespace Common::Logging;
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::ClassesEx;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t updatesThisFrame = 0;
            static uint64_t lastFrame = 0;
            static uint64_t o_func = 0;
            void __fastcall cb_hook(CProjectileExt* pExtProjectile, int pad, float* pSGameTime) {
                if (lastFrame != currentFrame) {
                    lastFrame = currentFrame;
                    updatesThisFrame = 0;
                }
                updatesThisFrame++;
                if (pExtProjectile->ALWAYS_UPDATE) {
                    return PLH::FnCast(o_func, &cb_hook)(pExtProjectile, pad, pSGameTime);
                }
                if (updatesThisFrame > maxProjectileUpdates && updatesThisFrame % 2 == 0) {
                    if (updatesThisFrame > maxProjectilesTotal) {
                        if (pExtProjectile->NO_CLEANUP) {
                            Logger::Print("A projectile was intended to be GC'd, but NO_CLEANUP was true, so the update was cancelled.");
                        }
                        else {
                            pExtProjectile->Kill();
                        }
                    }
                    return;
                }
                PLH::FnCast(o_func, &cb_hook)(pExtProjectile, pad, pSGameTime);
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
