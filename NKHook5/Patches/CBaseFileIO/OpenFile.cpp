#include "OpenFile.h"

#include <Extensions/Extension.h>
#include <Extensions/ExtensionManager.h>
#include <Files/File.h>
#include <Logging/Logger.h>

#include "../../Assets/Asset.h"
#include "../../Assets/AssetServer.h"
#include "../../Classes/CBaseFileIO.h"
#include "../../Classes/CFile.h"
#include "../../Classes/CUnzippedFile.h"
#include "../../Classes/CZipFile.h"
#include "../../Classes/IFile.h"
#include "../../Signatures/Signature.h"

#include <filesystem>
#include <string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CBaseFileIO
        {
            using namespace Common;
            using namespace Common::Extensions;
            using namespace Common::Files;
            using namespace Common::Logging;
            using namespace Common::Logging::Logger;
            using namespace NKHook5;
            using namespace NKHook5::Assets;
            using namespace NKHook5::Signatures;
            namespace fs = std::filesystem;

            static uint64_t o_func;
            static Classes::CZipFile* assetsArchive;
            Classes::IFile* __fastcall cb_hook(Classes::CBaseFileIO* pCBaseFileIO, int pad, std::string& assetPath, int policy, int eFileOpenMode) {
                //return PLH::FnCast(o_func, cb_hook)(pCBaseFileIO, pad, assetPath, policy, eFileOpenMode);
                /*
                Because both CFile and CUnzippedFile implement IFile, maybe we can just return a CUnzippedFile?
                */

                //Get the extensions for the file
                std::vector<Extension*> extsForFile = ExtensionManager::GetByTarget(assetPath);

                Classes::CUnzippedFile* pAsset = nullptr;

                std::string archivePath = "./Assets/BTD5.jet";
                if (assetsArchive == nullptr) {
                    assetsArchive = new Classes::CZipFile();
                    assetsArchive->Open(archivePath);
                }

                ghstl::string error;
                pAsset = assetsArchive->LoadFrom(assetPath, error);
#ifdef _DEBUG
                if (error.length() > 0) {
                    printf("%s\n", error.c_str());
                }
#endif

                //return pAsset;

                /* Ok so calling this function un-corrupts the stack? */
                Classes::CFile* resultFile = (Classes::CFile*)PLH::FnCast(o_func, cb_hook)(pCBaseFileIO, pad, assetPath, policy, eFileOpenMode);
                /* But result file returns with the data of pAsset ?? which is good but the fuck? */
                return resultFile;
            }

            auto OpenFile::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CBaseFileIO_OpenFile);
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