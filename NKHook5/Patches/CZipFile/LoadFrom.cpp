#include "LoadFrom.h"

#include "../../Classes/CZipFile.h"
#include "../../Classes/CUnzippedFile.h"

#include "../../AssetInjector/InjectionManager.h"
#include "../../Extensions/ExtensionManager.h"

#include <stdint.h>
#include <ghstl/string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CZipFile
        {
            using namespace NKHook5::AssetInjector;
            using namespace NKHook5::Extensions;

            uint64_t o_func;
            Classes::CUnzippedFile* __fastcall cb_hook(Classes::CZipFile* pBundle, uint32_t pad, ghstl::string* assetPath, void* param_2, ghstl::string* archivePassword) {
                std::vector<Extension*> extsForFile = ExtensionManager::GetByTarget(assetPath->cpp_str());
                Asset* injectedAsset = InjectionManager::FindInjectedAsset(assetPath->cpp_str());
                
                Classes::CUnzippedFile* pAsset = nullptr;

                if (injectedAsset) {
                    if (injectedAsset->GetPath() == assetPath->cpp_str()) {
                        pAsset = new Classes::CUnzippedFile();
                        pAsset->filePath = injectedAsset->GetPath();
                        pAsset->fileSize = injectedAsset->GetSizeOnHeap();
                        pAsset->fileContent = injectedAsset->GetAssetOnHeap();
                        return pAsset;
                    }
                }
                if(!pAsset)
                    pAsset = PLH::FnCast(o_func, &cb_hook)(pBundle, pad, assetPath, param_2, archivePassword);

                for (Extension* ext : extsForFile) {
                    ext->UseData(pAsset->fileContent, pAsset->fileSize);
                }
            }

            auto LoadFrom::Apply() -> bool
            {
                const uintptr_t address = Utils::FindPattern(Signatures::CZipFile::SIG_LOADFROM);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
                    if (detour->hook())
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