#include "LoadFrom.h"

#include "../../Classes/CZipFile.h"
#include "../../Classes/CUnzippedFile.h"
#include "../../AssetInjector/InjectionManager.h"
#include "../../Extensions/ExtensionManager.h"
#include "../../Signatures/Signature.h"
#include "../../Util/Json/MergedDocument.h"

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
            using namespace NKHook5::Util;
            using namespace NKHook5::Util::Json;
            using namespace Signatures;

            uint64_t o_func;
            Classes::CUnzippedFile* __fastcall cb_hook(Classes::CZipFile* pBundle, uint32_t pad, const std::string& assetPath, void* param_2, std::string& archivePassword) {
                std::vector<Extension*> extsForFile = ExtensionManager::GetByTarget(assetPath);
                AssetLoader* currentLoader = InjectionManager::GetLoader();
                Asset* injectedAsset = currentLoader->FindInjectedAsset(assetPath);
                
                Classes::CUnzippedFile* pAsset = nullptr;

                if(!pAsset)
                    pAsset = ((Classes::CUnzippedFile*(__thiscall*)(void*, const std::string&, void*, const std::string&))o_func)(pBundle, assetPath, param_2, archivePassword);

                if (injectedAsset != nullptr) {
                    if (injectedAsset->ExpectsMerge() && pAsset != nullptr) {
                        try {
                            std::string injectedStr = std::string((char*)injectedAsset->GetAssetOnHeap(), injectedAsset->GetSizeOnHeap());
                            std::string baseStr = std::string((char*)pAsset->fileContent, pAsset->fileSize);

                            nlohmann::ordered_json injectedJson = nlohmann::ordered_json::parse(injectedStr);
                            nlohmann::ordered_json baseJson = nlohmann::ordered_json::parse(baseStr);

                            MergedDocument merger;
                            merger.Add(baseJson);
                            merger.Add(injectedJson);
                            std::string merged = merger.GetMerged().dump();

                            if (pAsset->fileContent) {
                                free(pAsset->fileContent);
                            }

                            pAsset->fileContent = malloc(merged.size());
                            memcpy_s(pAsset->fileContent, merged.size(), merged.data(), merged.size());
                            pAsset->fileSize = merged.size();
                        }
                        catch (std::exception& ex) {
                            printf("Failed to merge asset that expected a merge! %s\n", ex.what());
                        }
                    }
                    else {
                        if(pAsset)
                            if (pAsset->fileContent)
                                free(pAsset->fileContent);
                        pAsset = new Classes::CUnzippedFile(injectedAsset);
                    }
                }

                if (pAsset != nullptr && pAsset->fileContent != nullptr) {
                    for (Extension* ext : extsForFile) {
                        ext->UseData(pAsset->fileContent, pAsset->fileSize);
                    }
                }

                if(injectedAsset)
                    injectedAsset->Release();

                return pAsset;
            }

            auto LoadFrom::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CZipFile_LoadFrom);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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