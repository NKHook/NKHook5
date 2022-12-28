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
            class CApplyStatusEffectTaskDetour : public Classes::CApplyStatusEffectTask {
            public:
                void __thiscall cb_hook(void* pBloon) {
                    return ((void(__thiscall*)(void*, void*))o_func)(this, pBloon);
                }
            };

            bool Fire::Apply()
            {
                const void* address = Signatures::GetAddressOf(Sigs::CApplyStatusEffectTask_Fire);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uintptr_t)address, (const uintptr_t)nfw::mftp(&CApplyStatusEffectTaskDetour::cb_hook), &o_func);
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
