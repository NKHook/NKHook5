#include "LoadAssets.h"

#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/CZipFile.h"
#include "../../Extensions/ExtensionManager.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace Extensions;

            static uint64_t o_func;
            static void* __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                printf("BTD5 began loading assets...\n");
                PLH::FnCast(o_func, &cb_hook)(gameInstance);
                printf("BTD5 assets loaded!\n");

                printf("Loading custom assets...\n");
                ghstl::string archivePath = "./Assets/BTD5.jet";
                ghstl::string empty = "";
                Classes::CZipFile assetsArchive;
                assetsArchive.Open(&archivePath);

                std::vector<Extension*> customDocuments = ExtensionManager::GetCustomDocuments();
                for (Extension* doc : customDocuments) {
                    const std::string& assetPath = doc->GetTarget();
                    ghstl::string ghstlAssetPath = assetPath;
                    
                    Classes::CUnzippedFile* unzipped = assetsArchive.LoadFrom(&ghstlAssetPath, &empty);
                    doc->UseData(unzipped->fileContent, unzipped->fileSize);
                }
                printf("Custom assets loaded!\n");
            }

            auto LoadAssets::Apply() -> bool
            {
                const uintptr_t address = Utils::FindPattern(Signatures::CBloonsTD5Game::SIG_LOADASSETS);
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