#include "Constructor.h"

#include "../../Classes/CBloonsTD5Game.h"
#include "../../AssetInjector/InjectionManager.h"
#include "../../Signatures/Signature.h"

NKHook5::Classes::CBloonsTD5Game* g_appPtr;

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace AssetInjector;
            using namespace Signatures;

            static uint64_t o_func;
            static void* __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                printf("Game Instance: %p\n", gameInstance);
                g_appPtr = gameInstance;
                printf("Game load started\n");
                printf("Initializing asset injector...\n");
                InjectionManager::SetupAssetLoader();
                printf("Asset injector ready!\n");
                return PLH::FnCast(o_func, &cb_hook)(gameInstance);
            }

            auto Constructor::Apply() -> bool
            {
                const void* address = GetAddressOf(Sigs::CBloonsTD5Game_CCTOR);
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