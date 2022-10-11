#include "LoadAssets.h"

#include "../../Util/NewFramework.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/CZipFile.h"
#include "../../Signatures/Signature.h"

#include <Extensions/ExtensionManager.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            using namespace Common::Extensions;
            using namespace Signatures;

            static uint64_t o_func;
            static void __fastcall cb_hook(Classes::CBloonsTD5Game* gameInstance) {
                printf("Loading custom assets...\n");
                printf("CWD: %s\n", std::filesystem::current_path().string().c_str());
                std::string archivePath = "./Assets/BTD5.jet";
                Classes::CZipFile* assetsArchive = new Classes::CZipFile();
                assetsArchive->Open(archivePath);

                std::vector<Extension*> customDocuments = ExtensionManager::GetCustomDocuments();
                ghstl::string error;
                for (Extension* doc : customDocuments) {
                    const std::string& assetPath = doc->GetTarget();

                    Classes::CUnzippedFile* unzipped = assetsArchive->LoadFrom(assetPath, error);
                    if (error.length() > 0) {
                        printf("%s\n", error.c_str());
                    }
                    if (unzipped) {
                        doc->UseData(unzipped->fileContent, unzipped->fileSize);
                        delete unzipped;
                    }
                }
                printf("Custom assets loaded!\n");

                printf("BTD5 began loading assets...\n");
                ((void(__thiscall*)(void*))o_func)(gameInstance);
                printf("BTD5 assets loaded!\n");
            }

            auto LoadAssets::Apply() -> bool
            {
                const void* address = GetAddressOf(Sigs::CBloonsTD5Game_LoadAssets);
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