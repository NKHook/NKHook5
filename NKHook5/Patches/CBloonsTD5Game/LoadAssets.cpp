#include "LoadAssets.h"

#include "../../Util/NewFramework.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/CZipFile.h"
#include "../../Extensions/StatusEffect/StatusDefinitionsExt.h"
#include "../../Signatures/Signature.h"

#include <Extensions/ExtensionManager.h>
#include <Extensions/StatusEffect/StatusFlagsExt.h>
#include <Logging/Logger.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace Common::Extensions;
            using namespace Common::Extensions::StatusEffect;
            using namespace Common;
            using namespace Common::Logging;
            using namespace Common::Logging::Logger;
            using namespace Signatures;
            using namespace Extensions;
            using namespace Extensions::StatusEffect;

            static uint64_t o_func;
            static void __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                Print(LogLevel::INFO, "Loading custom assets...");
                Print(LogLevel::INFO, "CWD: %s", std::filesystem::current_path().string().c_str());
                nfw::string archivePath = "./Assets/BTD5.jet";
                auto* assetsArchive = new Classes::CZipFile();
                assetsArchive->Open(archivePath);

                std::vector<Extension*> customDocuments = ExtensionManager::GetCustomDocuments();
                nfw::string error;
                for (Extension* doc : customDocuments) {
                    const std::string& assetPath = doc->GetTarget();

                    Classes::CUnzippedFile* unzipped = assetsArchive->LoadFrom(nfw::string(assetPath), error);
                    if (error.length() > 0) {
                        Print(LogLevel::ERR, "%s", error.c_str());
                    }
                    if (unzipped) {
                        doc->UseData(unzipped->fileContent, unzipped->fileSize);
                        delete unzipped;
                    }
                }
                auto statusDefs = ExtensionManager::Get<StatusDefinitionsExt>();
                auto statusFlags = ExtensionManager::Get<StatusFlagsExt>();
                for (const std::string& flag : statusFlags->GetFlags())
                {
                    nfw::string effectFile = "Assets/JSON/StatusDefinitions/" + nfw::string(flag) + ".status";
                    Classes::CUnzippedFile* unzipped = assetsArchive->LoadFrom(effectFile, error);
                    statusDefs->UseData(unzipped->fileContent, unzipped->fileSize);
                }
                Print(LogLevel::INFO, "Custom assets loaded!");

                Print(LogLevel::INFO, "BTD5 began loading assets...");
                ((void(__thiscall*)(void*))o_func)(gameInstance);
                Print(LogLevel::INFO, "BTD5 assets loaded!");
            }

            auto LoadAssets::Apply() -> bool
            {
                const void* address = GetAddressOf(Sigs::CBloonsTD5Game_LoadAssets);
                if(address)
                {
                    auto* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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