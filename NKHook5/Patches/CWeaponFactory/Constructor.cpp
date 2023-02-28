#include "Constructor.h"

#include <Logging/Logger.h>

#include "../../Classes/CWeaponFactory.h"
#include "../../Signatures/Signature.h"

NKHook5::Classes::CWeaponFactory* g_weaponFactory = nullptr;

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

namespace NKHook5
{
    namespace Patches
    {
        namespace CWeaponFactory
        {
            using namespace Signatures;

            static uint64_t o_func;
            Classes::CWeaponFactory* __fastcall cb_hook(Classes::CWeaponFactory* self, size_t pad, uint32_t unk1, uint32_t unk2)
            {    
                g_weaponFactory = self;
#ifdef _DEBUG
                Print(LogLevel::INFO, "g_weaponFactory: %p", g_weaponFactory);
#endif
                return PLH::FnCast(o_func, &cb_hook)(self, pad, unk1, unk2);
            }

            auto Constructor::Apply() -> bool
            {
                void* address = Signatures::GetAddressOf(Sigs::CWeaponFactory_CCTOR);
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