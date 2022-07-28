#include "FindText.h"

#include <ghstl/string>
#include <string>
#include "../../Classes/CLoc.h"
#include "../../Classes/Texts.h"
#include "../../Extensions/Generic/LocExtension.h"
#include "../../Extensions/ExtensionManager.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            using namespace Signatures;

            static uint64_t o_func;
            static std::map<std::string, Classes::SLang*> generatedTexts;
            Classes::SLang* __fastcall cb_hook(Classes::CLoc* pCLoc, uint32_t pad, ghstl::string* textKey, Classes::SLangDef* desiredLang) {
                if (generatedTexts.count(textKey->cpp_str())) {
                    return generatedTexts[textKey->cpp_str()];
                }
                Extensions::Extension* pLocExt = Extensions::ExtensionManager::GetByName("EnglishLocs");
                Extensions::Generic::LocExtension* locExt = (Extensions::Generic::LocExtension*)pLocExt;
                auto locs = locExt->GetLocs();
                for (auto loc : locs) {
                    if (loc.id == textKey->cpp_str()) {
                        Classes::SLang* generatedLoc = new Classes::SLang();
                        generatedLoc->key = 0;
                        generatedLoc->id = loc.id;
                        generatedLoc->l = loc.l;
                        generatedLoc->val = loc.value;
                        generatedTexts[textKey->cpp_str()] = generatedLoc;
                        return generatedLoc;
                    }
                }
                return PLH::FnCast(o_func, &cb_hook)(pCLoc, pad, textKey, desiredLang);
            }

            auto FindText::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CLoc_FindText);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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