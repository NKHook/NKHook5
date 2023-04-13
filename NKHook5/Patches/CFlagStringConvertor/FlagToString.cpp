#include "FlagToString.h"

#include "../../Util/NewFramework.h"
#include "../../Classes/CBloonFactory.h"
#include "../../Classes/CFlagStringConvertor.h"
#include "../../Classes/CTowerFactory.h"
#include "../../Classes/CWeaponFactory.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"
#include <intrin.h>

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
            nfw::string* __fastcall cb_hook(Classes::CFlagStringConvertor* self, uint32_t pad, nfw::string* result, uint32_t categoryId, uint64_t numericId) {
                nfw::string* resultStr = PLH::FnCast(o_func, &cb_hook)(self, pad, result, categoryId, numericId);
                //Code for tower id injections
                if (self == g_towerFactory) {
                    if (categoryId == 0) {
                        //Use the custom tower flag manager to manage flags instead
                        resultStr->assign(g_towerFlags.GetName(numericId));
                    }
                }

                //Code for status effect id injections
                if (self == g_bloonFactory)
                {
                    if (categoryId == 0 /*Bloon type ids category*/)
                    {
                        resultStr->assign(g_bloonFlags.GetName(numericId));
                    }
                    if (categoryId == 1 /*Status effect category*/)
                    {
                        resultStr->assign(g_bloonStatusFlags.GetName(numericId));
                    }
                }

                if (self == g_weaponFactory)
                {
                    //Weapon types category
                    if (categoryId == 0)
                    {
                        resultStr->assign(g_weaponFlags.GetName(numericId));
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