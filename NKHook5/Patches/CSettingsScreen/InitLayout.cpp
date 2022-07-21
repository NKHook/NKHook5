#include "InitLayout.h"

#include "../../Classes/CSettingsScreen.h"
#include "../../Classes/CTextObject.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CSettingsScreen
        {
            uint64_t o_func;
            void* __fastcall cb_hook(Classes::CSettingsScreen* self, int pad, int param_1) {
                void* result = PLH::FnCast(o_func, &cb_hook)(self, pad, param_1);

                return result;
            }

            auto InitLayout::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B D9 ?? 9D ?? ?? ?? ?? ?? ?? ?? ?? 85 ?? ?? ?? ?? ?? ?? ?? ?? ?? 85 ?? ?? ?? ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 6A");
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
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
        } // namespace CBasePositionableObject
    }
}
