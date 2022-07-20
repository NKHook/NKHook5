#include "GetScreenForParadigm.h"

#include <ghstl/string>
#include "../../Classes/CGameSystemPointers.h"
#include "../../Classes/CBloonsBaseScreen.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Screens
        {
            uint64_t o_func;
            Classes::CBloonsBaseScreen* __fastcall cb_hook(const ghstl::string* screenName, int deviceType, Classes::CGameSystemPointers* pCGameSystemPointers) {
                Classes::CBloonsBaseScreen* res = PLH::FnCast(o_func, &cb_hook)(screenName, deviceType, pCGameSystemPointers);
                return res;
            }

            auto GetScreenForParadigm::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 8B ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? 45 ?? ?? ?? ?? ?? 83");
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
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