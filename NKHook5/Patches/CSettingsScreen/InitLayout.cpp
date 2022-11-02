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
                ghstl::string nkhookText("NKHook5 v" STRING(NKHOOK_BUILD_TAG) " (" STRING(NKHOOK_BUILD_VERSION) ")");
                boost::shared_ptr<Classes::CFont>* pCFont = &self->pMenuFont;
                Classes::Vec2F location(160, -100);
                //Looks like a memory leak, but the game deletes it when its no longer used.
                Classes::CTextObject* testObj = new Classes::CTextObject(&location, pCFont, &nkhookText);
                Classes::Vec2F textScale(0.5, 0.5);
                testObj->Scale(textScale);
                testObj->SetRotation(40);
                Classes::Color c(0xFF, 0xFF, 0xFF, 0xFF);
                testObj->SetColor(&c, 0);
                self->parentObj->AddChild(testObj);

                printf("Primary sheet: %s", self->buttonStyle.primarySheet.c_str());
                printf("Secondary sheet: %s", self->buttonStyle.secondarySheet.c_str());

                Classes::CTextureManager* textureMgr = self->basePointers.textureManager;
                Classes::SSpriteInfo* buttonSprite = textureMgr->GetSpriteInfoPtr("newshared", "newshared_button");
                Classes::SSpriteInfo* resumeSprite = textureMgr->GetSpriteInfoPtr("shared_sheet", "resume");

                Classes::SMainButtonStyle style;
                style.font = self->pMenuFont;
                self->modsButton = new Classes::CMainButton(self->basePointers.pCInput, self, "mods", "Mods", buttonSprite, resumeSprite, style);
                self->parentObj->AddChild(&self->modsButton->sprite);

                /*printf("Testing custom menu");
                Classes::ScriptedScreenData data("Assets/Scripts/testMenu.lua");
                Classes::ScriptedScreen* customScreen = new Classes::ScriptedScreen(self->pCGameSystemPointers);
                self->basePointers.pCScreenManager->OpenPopup(customScreen, &data);
                printf("Test passed");*/
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
