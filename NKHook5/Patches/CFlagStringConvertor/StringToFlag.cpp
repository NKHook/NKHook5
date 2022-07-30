#include "StringToFlag.h"

#include "../../Classes/CTowerFactory.h"
#include "../../Classes/CFlagStringConvertor.h"
#include "../../Signatures/Signature.h"
#include <ghstl/string>

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
extern std::vector<ghstl::string> g_moddedTowerTypes;

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            using namespace Signatures;

            static uint64_t o_func;
            uint64_t __fastcall cb_hook(Classes::CFlagStringConvertor* self, int pad, int categoryId, ghstl::string* textId) {
                if (self == &g_towerFactory->flagStringConvertor) {
                    if (categoryId == 0 || categoryId == 5) {
                        for (uint64_t i = 0; i < g_moddedTowerTypes.size(); i++) {
                            if (g_moddedTowerTypes[i].cpp_str() == textId->cpp_str()) {
                                return MAX_TOWER_ID + i + 1;
                            }
                        }
                    }
                }
                return PLH::FnCast(o_func, &cb_hook)(self, pad, categoryId, textId);
            }

            auto StringToFlag::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_StringToFlag);
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