#include "Constructor.h"

#include <ghstl/string>
#include "../../Classes/CTowerFactory.h"

NKHook5::Classes::CTowerFactory* g_towerFactory = nullptr;

namespace NKHook5
{
    namespace Patches
    {
        namespace CTowerFactory
        {
            static uint64_t o_func;
            Classes::CTowerFactory* __fastcall cb_hook(Classes::CTowerFactory* self) {
                
                g_towerFactory = self;
                printf("g_towerFactory: %p", g_towerFactory);
                return PLH::FnCast(o_func, &cb_hook)(self);
            }

            auto Constructor::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern(Signatures::CTowerFactory::SIG_CCTOR);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
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