#include "Constructor.h"

#include <ghstl/string>
#include "../../Classes/CTowerFactory.h"
#include "../../Signatures/Signature.h"

NKHook5::Classes::CTowerFactory* g_towerFactory = nullptr;

namespace NKHook5
{
    namespace Patches
    {
        namespace CTowerFactory
        {
            using namespace Signatures;

            static uint64_t o_func;
            Classes::CTowerFactory* __fastcall cb_hook(Classes::CTowerFactory* self, void* pad, void* param_1, void* param_2) {
                
                g_towerFactory = self;
                printf("g_towerFactory: %p", g_towerFactory);
                return ((Classes::CTowerFactory*(__thiscall*)(void*, void*, void*))o_func)(self, param_1, param_2);
                //return PLH::FnCast(o_func, &cb_hook)(self);
            }

            auto Constructor::Apply() -> bool
            {
                void* address = Signatures::GetAddressOf(Sigs::CTowerFactory_CCTOR);
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