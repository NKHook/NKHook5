#include "GetText.h"

#include <ghstl/string>
#include <string>
#include "../../Classes/CLoc.h"
#include "../../Classes/Texts.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            using namespace Signatures;

            static uint64_t o_func;
            void* __fastcall cb_hook(Classes::CLoc* pCLoc, uint32_t pad, ghstl::string* result, Classes::eTexts textId, Classes::SLangDef* language) {
                void* res = PLH::FnCast(o_func, &cb_hook)(pCLoc, pad, result, textId, language);
                //printf("ID: %x Result: %s\n", textId, result->c_str());
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