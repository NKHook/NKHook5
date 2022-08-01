#include "FlagToString.h"

#include "../../Util/NewFramework.h"
#include "../../Classes/CFlagStringConvertor.h"
#include "../../Classes/CTowerFactory.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"
#include <ghstl/string>
#include <intrin.h>

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
extern NKHook5::Util::FlagManager g_towerFlags;

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            using namespace Signatures;

            static uint64_t o_func;
            ghstl::string* __fastcall cb_hook(Classes::CFlagStringConvertor* self, uint32_t pad, ghstl::string* result, uint32_t categoryId, uint64_t numericId) {
                ghstl::string* resultStr = PLH::FnCast(o_func, &cb_hook)(self, pad, result, categoryId, numericId);
                if (self == &g_towerFactory->flagStringConvertor) {
                    if (categoryId == 0) {
                        resultStr->assign(g_towerFlags.GetName(numericId));
                    }
                }
                return resultStr;
            }

            auto FlagToString::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_FlagToString);
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