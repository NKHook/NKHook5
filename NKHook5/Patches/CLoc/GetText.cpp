#include "GetText.h"

#include <ghstl/string>
#include <string>
#include "../../Classes/CLoc.h"
#include "../../Classes/Texts.h"
#include "../../Signatures/Signature.h"

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
            void* __fastcall cb_hook(Classes::CLoc* pCLoc, uint32_t pad, std::string* result, Classes::eTexts textId, Classes::SLangDef* language) {
                void* res = PLH::FnCast(o_func, &cb_hook)(pCLoc, pad, result, textId, language);
#ifdef DEBUG
                Print(LogLevel::DEBUG, "ID: %x Result: %s", textId, result->c_str());
#endif
                return res;
            }

            auto GetText::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CLoc_GetText);
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
        }
    }
}