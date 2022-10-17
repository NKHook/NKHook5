#include "Init.h"

#include "../../Classes/CGameScreen.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CGameScreen
        {
            using namespace NKHook5;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func;
            void __fastcall cb_hook(Classes::CGameScreen* pCGameScreen, int pad, Classes::IScreenData* pScreenData) {
                PLH::FnCast(o_func, &cb_hook)(pCGameScreen, pad, pScreenData);
                
            }

            auto Init::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CGameScreen_Init);
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
        } // namespace CGameScreen
    }
}
