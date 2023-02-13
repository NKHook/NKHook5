#include "Constructor.h"

#include <Logging/Logger.h>
#include <Extensions/ExtensionManager.h>

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
            using namespace Common::Extensions;
            using namespace NKHook5;
            using namespace NKHook5::Assets;
            using namespace NKHook5::Signatures;
            namespace fs = std::filesystem;

            static uint64_t o_func;
            static void* __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                Print("Game Instance: %p", gameInstance);
                g_appPtr = gameInstance;
                Print("Game load started");
                Print("Loading Mods...");
                fs::path cwd = fs::current_path();
                fs::path modsDir = cwd / "Mods";
                if (!fs::exists(modsDir)) {
                    fs::create_directories(modsDir);
                }
                AssetServer* server = AssetServer::GetServer();
                std::map<LoadOrder, std::vector<ModAssetSource*>> sources;
                for (const auto& mod : fs::directory_iterator(modsDir))
                {
                    try {
                        ModAssetSource* source = new ModAssetSource(mod);
                        std::shared_ptr<ModArchive> modArch = source->GetModArch();
                        const ModInfo& modInfo = modArch->GetInfo();
                        const std::optional<LoadOrder>& order = modInfo.GetLoadOrder();
                        if (order.has_value())
                            sources[*order].push_back(source);
                        else
                            sources[LoadOrder::ANY].push_back(source);
                    }
                    catch (std::exception& ex) {
                        Print("An error occured while preparing mod initialization: %s", ex.what());
                    }
                }
                LoadOrder priorityList[] = {
                    LoadOrder::BASE,
                    LoadOrder::FIRST,
                    LoadOrder::ANY,
                    LoadOrder::LAST
                };
                for (LoadOrder currentTime : priorityList)
                {
                    for (const auto& modSource : sources[currentTime])
                    {
                        try {
                            server->AddSource(modSource);
                            std::shared_ptr<ModArchive> modArch = modSource->GetModArch();
                            if (modSource->Has(ExtensionManager::GetByName("MergeIgnore")->GetTarget()))
                            {
                                if (currentTime != LoadOrder::BASE)
                                {
                                    Print(LogLevel::ERR, "'%s' uses MergeIgnore, but without 'BASE' load_order!", modArch->GetInfo().GetName().c_str());
                                    Print(LogLevel::SUCCESS, "Add a 'load_order' entry to the mod's modinfo.json file with the value 'BASE'");
                                }
                            }
                            const ModInfo& modInfo = modArch->GetInfo();
                            Print("Loading %s", modInfo.GetName().c_str());
                        }
                        catch (std::exception& ex) {
                            Print("An error occured while loading a mod: %s", ex.what());
                        }
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