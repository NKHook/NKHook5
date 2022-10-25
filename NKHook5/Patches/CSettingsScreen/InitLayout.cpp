#include "InitLayout.h"

#include "../../Classes/CFont.h"
#include "../../Classes/CFontManager.h"
#include "../../Classes/CSettingsScreen.h"
#include "../../Classes/CTextObject.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/Vec2F.h"
#include "../../Utils.h"
#include "../../Signatures/Signature.h"

#include <Util/Macro.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CSettingsScreen
        {
            using namespace Signatures;

            uint64_t o_func;
            void __fastcall cb_hook(Classes::CSettingsScreen* self, int pad, int param_1) {
                //((void(__thiscall*)(void*, int))o_func)(self, param_1);
                PLH::FnCast(o_func, &cb_hook)(self, pad, param_1);
                printf("CSettingsScreen*: %p\n", self);
                printf("SettingScreen inited\n");
                ghstl::string nkhookText("NKHook5 v" STRING(NKHOOK_BUILD_TAG) " (" STRING(NKHOOK_BUILD_VERSION) ")");
                printf("Made watermark\n");
                boost::shared_ptr<Classes::CFont>* pCFont = &self->pMenuFont;
                printf("Retrieved font\n");
                Classes::Vec2F location(160, -100);
                printf("Created location\n");
                //Looks like a memory leak, but the game deletes it when its no longer used.
                Classes::CTextObject* testObj = new Classes::CTextObject(&location, pCFont, &nkhookText);
                Classes::Vec2F textScale(0.5, 0.5);
                testObj->Scale(textScale);
                testObj->SetRotation(40);
                Classes::Color c(0xFF, 0xFF, 0xFF, 0xFF);
                testObj->SetColor(&c, 0);
                printf("Made text object for watermark (%p)\n", testObj);
                self->parentObj->AddChild(testObj);
                printf("Added object to screen\n");
            }

            auto InitLayout::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CSettingsScreen_InitLayout);
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
