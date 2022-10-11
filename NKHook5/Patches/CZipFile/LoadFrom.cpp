#include "LoadFrom.h"

#include "../../Classes/CZipFile.h"
#include "../../Classes/CUnzippedFile.h"
#include "../../Signatures/Signature.h"

#include <Extensions/ExtensionManager.h>
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
            using namespace Common::Util;
            using namespace Common::Util::Json;
            using namespace Common::Util::Xml;
            using namespace Signatures;

            uint64_t o_func;
            Classes::CUnzippedFile* __fastcall cb_hook(Classes::CZipFile* pBundle, uint32_t pad, const std::string& assetPath, void* param_2, std::string& archivePassword) {
                std::vector<Extension*> extsForFile = ExtensionManager::GetByTarget(assetPath);
                
                Classes::CUnzippedFile* pAsset = nullptr;

                if(!pAsset)
                    pAsset = ((Classes::CUnzippedFile*(__thiscall*)(void*, const std::string&, void*, const std::string&))o_func)(pBundle, assetPath, param_2, archivePassword);

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