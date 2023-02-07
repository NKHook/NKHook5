#include "FindText.h"

#include <string>
#include "../../Classes/CLoc.h"
#include "../../Classes/Texts.h"
#include "../../Signatures/Signature.h"

#include <Extensions/ExtensionManager.h>
#include <Logging/Logger.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            using namespace Signatures;
            using namespace Common;
            using namespace Common::Logging;
            using namespace Common::Logging::Logger;

            static uint64_t o_func;
            static std::map<std::string, Classes::SLang*> generatedTexts;
            Classes::SLang* __fastcall cb_hook(Classes::CLoc* pCLoc, uint32_t pad, std::string* textKey, Classes::SLangDef* desiredLang) {
                Classes::SLang* result = PLH::FnCast(o_func, &cb_hook)(pCLoc, pad, textKey, desiredLang);
#ifdef DEBUG
                if (result == nullptr)
                    return result;
                Print(LogLevel::DEBUG, "ID: %s Result: %s", textKey->c_str(), result->val.c_str());
#endif
                return result;
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