#include "Constructor.h"

#include <Logging/Logger.h>

#include "../../Assets/AssetServer.h"
#include "../../Assets/ModAssetSource.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Signatures/Signature.h"

#include <filesystem>

NKHook5::Classes::CBloonsTD5Game* g_appPtr;

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace Common;
            using namespace Common::Logging;
            using namespace Common::Logging::Logger;
            using namespace NKHook5;
            using namespace NKHook5::Assets;
            using namespace NKHook5::Signatures;
            namespace fs = std::filesystem;

            static uint64_t o_func;
            static void* __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                Print("Game Instance: %p\n", gameInstance);
                g_appPtr = gameInstance;
                Print("Game load started\n");
                Print("Loading Mods...");
                fs::path cwd = fs::current_path();
                fs::path modsDir = cwd / "Mods";
                if (!fs::exists(modsDir)) {
                    fs::create_directories(modsDir);
                }
                AssetServer* server = AssetServer::GetServer();
                for (const auto& mod : fs::directory_iterator(modsDir)) {
                    try {
                        server->AddSource(new ModAssetSource(mod));
                    }
                    catch (std::exception& ex) {
                        Print("An error occured while loading a mod: %s", ex.what());
                    }
                }
                Print("Mods loaded!");
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