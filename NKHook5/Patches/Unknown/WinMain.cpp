#include "WinMain.h"

#include <ghstl/string>
#include "../../Classes/CGameSystemPointers.h"
#include "../../Classes/CBloonsBaseScreen.h"
#include "../../Classes/CPopupScreenBase.h"
#include "../../Classes/DeviceType.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Unknown
        {
            using namespace Signatures;

            uint64_t o_func;
            void __stdcall hkWinMain(HINSTANCE param_1, HINSTANCE param_2, char* param_3, int param_4) {
                if(param_3)
                    param_3[0] = 0;
                printf("Cleared CMDLINE\n");
                return PLH::FnCast(o_func, &hkWinMain)(param_1, param_2, param_3, 0);
            }

            auto WinMain::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::Unknown_WinMain);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&hkWinMain, &o_func);
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