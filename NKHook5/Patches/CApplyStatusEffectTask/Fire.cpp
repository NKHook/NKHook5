#include "Fire.h"

#include "../../Classes/CApplyStatusEffectTask.h"
#include "../../Classes/CBloon.h"
#include "../../Signatures/Signature.h"
#include "../../Util/NewFramework.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CApplyStatusEffectTask
        {
            using namespace NKHook5;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func = 0;
            void __fastcall cb_hook(void* task, void* pad, void* bloon, float unk, float unk2, float unk3, float unk4) {
                return PLH::FnCast(o_func, &cb_hook)(task, pad, bloon, unk, unk2, unk3, unk4);
            }

            bool Fire::Apply()
            {
                const void* address = Signatures::GetAddressOf(Sigs::CApplyStatusEffectTask_Fire);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uintptr_t)address, (const uintptr_t)&cb_hook, &o_func);
                    if (detour->hook())
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
