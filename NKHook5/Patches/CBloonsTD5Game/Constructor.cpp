#include "Constructor.h"

#include "../../Classes/CBloonsTD5Game.h"
#include "../../AssetInjector/InjectionManager.h"

NKHook5::Classes::CBloonsTD5Game* g_appPtr;

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace AssetInjector;

            static uint64_t o_func;
            static void* __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                printf("Game Instance: %p\n", gameInstance);
                g_appPtr = gameInstance;
                printf("Game load started\n");
                printf("Initializing asset injector...\n");
                InjectionManager::Initialize();
                printf("Asset injector ready!\n");
                return PLH::FnCast(o_func, &cb_hook)(gameInstance);
            }

            auto Constructor::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern(NKHook5::Signatures::CBloonsTD5Game::SIG_CCTOR);
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