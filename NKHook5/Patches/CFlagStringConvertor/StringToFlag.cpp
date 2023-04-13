#include "StringToFlag.h"

#include "../../Util/NewFramework.h"
#include "../../Classes/CBloonFactory.h"
#include "../../Classes/CTowerFactory.h"
#include "../../Classes/CFlagStringConvertor.h"
#include "../../Classes/CWeaponFactory.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"
#include <ghstl/string>

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
extern NKHook5::Util::FlagManager g_towerFlags;
extern NKHook5::Classes::CBloonFactory* g_bloonFactory;
extern NKHook5::Util::FlagManager g_bloonFlags;
extern NKHook5::Util::FlagManager g_bloonStatusFlags;
extern NKHook5::Classes::CWeaponFactory* g_weaponFactory;
extern NKHook5::Util::FlagManager g_weaponFlags;

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            using namespace Signatures;

            static uint64_t o_func;
            uint64_t __fastcall cb_hook(Classes::CFlagStringConvertor* self, int pad, int categoryId, ghstl::string* textId) {
                uint64_t result = PLH::FnCast(o_func, &cb_hook)(self, pad, categoryId, textId);
                if (self == g_towerFactory) {
                    if (categoryId == 0) {
                        result = g_towerFlags.GetFlag(textId->cpp_str());
                    }
                }

                if (self == g_bloonFactory)
                {
                    if (categoryId == 0)
                    {
                        result = g_bloonFlags.GetFlag(textId->cpp_str());
                    }
                    if (categoryId == 1)
                    {
                        result = g_bloonStatusFlags.GetFlag(textId->cpp_str());
                    }
                }

                if (self == g_weaponFactory)
                {
                    if (categoryId == 0)
                    {
                        result = g_weaponFlags.GetFlag(textId->cpp_str());
                    }
                }

                return result;
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