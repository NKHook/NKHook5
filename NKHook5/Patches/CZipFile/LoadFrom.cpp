#include "LoadFrom.h"

#include "../../Assets/AssetServer.h"
#include "../../Classes/CZipFile.h"
#include "../../Classes/CUnzippedFile.h"
#include "../../Signatures/Signature.h"

#include <Extensions/ExtensionManager.h>
#include <Files/File.h>
#include <Logging/Logger.h>
#include <Util/Json/MergedDocument.h>
#include <Util/Xml/ReflectedDocument.h>

#include <stdint.h>
#include <ghstl/string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CZipFile
        {
            using namespace Common::Extensions;
            using namespace Common::Files;
            using namespace Common::Logging;
            using namespace Common::Logging::Logger;
            using namespace Common::Util;
            using namespace Common::Util::Json;
            using namespace Common::Util::Xml;
            using namespace NKHook5;
            using namespace NKHook5::Signatures;
            using namespace NKHook5::Assets;

            uint64_t o_func;
            Classes::CUnzippedFile* __fastcall cb_hook(Classes::CZipFile* pBundle, uint32_t pad, const std::string& assetPath, void* param_2, std::string& archivePassword) {
                //Get the extensions for the file
                std::vector<Extension*> extsForFile = ExtensionManager::GetByTarget(assetPath);

                Classes::CUnzippedFile* pAsset = nullptr;

                //Get the vanilla asset
                if(!pAsset)
                    pAsset = ((Classes::CUnzippedFile*(__thiscall*)(void*, const std::string&, void*, const std::string&))o_func)(pBundle, assetPath, param_2, archivePassword);

                //Store the vanilla data into a vector
                std::vector<uint8_t> vanillaData;

                if (pAsset) {
                    vanillaData = std::vector<uint8_t>(pAsset->fileSize);
                    memcpy_s(vanillaData.data(), vanillaData.size(), pAsset->fileContent, pAsset->fileSize);
                }
                else {
                    if (fs::exists(assetPath)) {
                        File vanillaFile;
                        vanillaFile.OpenRead(assetPath);
                        vanillaData = vanillaFile.ReadBytes();
                        vanillaFile.Close();
                    }
                    else {
                        Print(LogLevel::ERR, "Failed to find asset: %s", assetPath.c_str());
                    }
                }

                if (!vanillaData.empty()) {
                    //Run extensions
                    for (Extension* ext : extsForFile) {
                        if (!ext->IsCustomDocument())
                            ext->UseData(vanillaData.data(), vanillaData.size());
                    }
                }

                //Get the AssetServer
                AssetServer* server = AssetServer::GetServer();
                //Serve the asset
                std::shared_ptr<Asset> servedAsset = server->Serve(assetPath, vanillaData);
                //If there is an asset to serve
                if (servedAsset != nullptr) {
                    if (pAsset) {
                        //Create a copy
                        void* contentCopy = malloc(servedAsset->GetData().size());
                        memcpy_s(
                            contentCopy,
                            servedAsset->GetData().size(),
                            servedAsset->GetData().data(),
                            servedAsset->GetData().size()
                        );
                        if (pAsset->fileContent) {
                            free(pAsset->fileContent);
                        }
                        //Place the new pointer and size into the asset structure
                        pAsset->fileContent = contentCopy;
                        pAsset->fileSize = servedAsset->GetData().size();
                    }
                    else {
                        pAsset = new Classes::CUnzippedFile(servedAsset);
                    }
                }

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