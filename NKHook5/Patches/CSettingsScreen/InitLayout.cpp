#include "InitLayout.h"

#include "../../Classes/CFont.h"
#include "../../Classes/CFontManager.h"
#include "../../Classes/CSettingsScreen.h"
#include "../../ClassesEx/CSettingsScreenExt.h"
#include "../../Classes/CTextObject.h"
#include "../../Classes/CTextureManager.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/CScreenManager.h"
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
        namespace CSettingsScreen
        {
            using namespace Signatures;

            static uint64_t o_func;
            static void __fastcall cb_hook(ClassesEx::CSettingsScreenExt* self, int pad, int param_1) {
                //((void(__thiscall*)(void*, int))o_func)(self, param_1);
                PLH::FnCast(o_func, &cb_hook)(self, pad, param_1);
                
                /* Modify the base game ui stuff */
                //Add the BTD5 text
                Classes::CTextObject* vanillaText = new Classes::CTextObject({ -100, -15 }, self->screenFont, "BTD5");
                vanillaText->SetColor(Classes::Colors::white, 0);
                vanillaText->Scale({ .75, .75 });
                self->rootObj->AddChild(vanillaText);

                //Move the vanilla UI elements
                self->languageGroup->SetXY({ -100, 0 });
                self->languageGroup->ForceUpdate();
                self->controlsGroup->SetXY({ -100, 60});
                self->controlsGroup->ForceUpdate();

                /* Custom settings ui stuff */
                //Add the NKHook5 text
                Classes::CTextObject* nkhookText = new Classes::CTextObject({ 100, -15 }, self->screenFont, "NKHook5");
                nkhookText->SetColor(Classes::Colors::white, 0);
                nkhookText->Scale({ .75, .75 });
                self->rootObj->AddChild(nkhookText);

                //Add the Mods button
                Classes::CTextureManager* textureMgr = self->basePointers.textureManager;
                Classes::SSpriteInfo* buttonSprite = textureMgr->GetSpriteInfoPtr("newshared", "newshared_button_wider");
                Classes::SMainButtonStyle style;
                style.font = self->screenFont;
                self->modsButton = new Classes::CMainButton(self->basePointers.pCInput, self, "mods", "Mods", buttonSprite, nullptr, style);
                self->modsButton->SetXY({ 100, 18 });
                self->rootObj->AddChild(self->modsButton);
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
