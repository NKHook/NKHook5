#include "FileExists.h"

#include <Logging/Logger.h>

#include "../../Assets/Asset.h"
#include "../../Assets/AssetServer.h"
#include "../../Classes/CBaseFileIO.h"
#include "../../Classes/CUnzippedFile.h"
#include "../../Classes/CZipFile.h"
#include "../../Classes/IFile.h"
#include "../../Signatures/Signature.h"

#include <ghstl/string>

#include <string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CBaseFileIO
        {
            using namespace Common;
            using namespace Common::Logging;
            using namespace Common::Logging::Logger;
            using namespace NKHook5;
            using namespace NKHook5::Assets;
            using namespace NKHook5::Signatures;

            static uint64_t o_func;
            static Classes::CZipFile* assetsArchive;
            bool __fastcall cb_hook(Classes::CBaseFileIO* pCBaseFileIO, int pad, std::string& assetPath, int policy) {
                bool result = false;

                //Get the AssetServer
                AssetServer* server = AssetServer::GetServer();
                //Check if an asset exists
                result = server->Has(assetPath);

                //If we cannot find the file
                if (!result) {
                    //Let the game try
                    result = PLH::FnCast(o_func, &cb_hook)(pCBaseFileIO, pad, assetPath, policy);
                }

#ifdef _DEBUG
                Print("Found %x: %s", result, assetPath.c_str());
#endif

                return result;
            }

            auto FileExists::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CBaseFileIO_FileExists);
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