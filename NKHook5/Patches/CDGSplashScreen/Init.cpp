#include "Init.h"

#include "../../Classes/CFont.h"
#include "../../Classes/CFontManager.h"
#include "../../Classes/CDGSplashScreen.h"
#include "../../Classes/CTextObject.h"
#include "../../Classes/CTextureManager.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/CScreenManager.h"
#include "../../Classes/IScreenData.h"
#include "../../Classes/ScriptedScreen.h"
#include "../../Classes/ScriptedScreenData.h"
#include "../../Classes/Vec2F.h"
#include "../../Utils.h"
#include "../../Signatures/Signature.h"

#include <Util/Macro.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CDGSplashScreen
        {
            using namespace Signatures;

            static uint64_t o_func;
            static void __fastcall cb_hook(Classes::CDGSplashScreen* self, int pad, Classes::IScreenData* screenData) {
                //((void(__thiscall*)(void*, int))o_func)(self, param_1);
                PLH::FnCast(o_func, &cb_hook)(self, pad, screenData);
            }

            auto Init::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CDGSplashScreen_Init);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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
