#include "Constructor.h"

#include "../../AssetInjector/InjectionManager.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace AssetInjector;

            uint64_t o_func;
            void* __fastcall cb_hook(void* gameInstance) {
                printf("Game load started\n");
                printf("Initializing asset injector...\n");
                InjectionManager::Initialize();
                printf("Asset injector ready!\n");
                return PLH::FnCast(o_func, &cb_hook)(gameInstance);
            }

            auto Constructor::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 53 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 ?? 75 ?? E8 ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 86");
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