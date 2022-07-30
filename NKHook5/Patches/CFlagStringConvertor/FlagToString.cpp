#include "FlagToString.h"

#include "../../Classes/CFlagStringConvertor.h"
#include "../../Classes/CTowerFactory.h"
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
            ghstl::string* __fastcall cb_hook(Classes::CFlagStringConvertor* self, uint32_t pad, ghstl::string* result, uint32_t categoryId, uint64_t numericId) {
                if (self == &g_towerFactory->flagStringConvertor) {
                    if (categoryId == 0 || categoryId == 5) {
                        if (numericId > MAX_TOWER_ID) {
                            uint64_t realId = (numericId - MAX_TOWER_ID) + 1;
                            ghstl::string* moddedId = &g_moddedTowerTypes.at(realId);
                            printf("ID: '%llx' corresponds to modded type '%s'", numericId, moddedId->c_str());
                            return moddedId;
                        }
                    }
                }
                return PLH::FnCast(o_func, &cb_hook)(self, pad, result, categoryId, numericId);
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