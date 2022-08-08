#include "Update.h"

#include "../../Signatures/Signature.h"

#define MAX_BLOON_UPDATES 256

extern uint64_t currentFrame;

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloon
        {
            using namespace NKHook5;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            uint64_t updatesThisFrame = 0;
            uint64_t lastFrame = currentFrame;
            static uint64_t o_func;
            void __fastcall cb_hook(void* pBloon, int pad, float* pSGameTime) {
                if (lastFrame != currentFrame) {
                    lastFrame = currentFrame;
                    updatesThisFrame = 0;
                }
                if (updatesThisFrame > MAX_BLOON_UPDATES) {
                    return;
                }
                updatesThisFrame++;
                PLH::FnCast(o_func, &cb_hook)(pBloon, pad, pSGameTime);
            }

            auto Update::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CBloon_Update);
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
