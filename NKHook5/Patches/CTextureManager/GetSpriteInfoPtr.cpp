#include "GetSpriteInfoPtr.h"

#include "../../Assets/Asset.h"
#include "../../Assets/AssetServer.h"
#include "../../Classes/CTextureManager.h"

#include <Extensions/Textures/SheetsExtension.h>
#include <Extensions/ExtensionManager.h>

#include <string>

namespace NKHook5 {
	namespace Patches {
		namespace CTextureManager {
            using namespace Common;
            using namespace Common::Extensions;
            using namespace Common::Extensions::Textures;
            using namespace NKHook5;
            using namespace NKHook5::Assets;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func = 0;
            static Classes::SSpriteInfo* __fastcall cb_hook(Classes::CTextureManager* self, void* pad, const std::string& sheetName, const std::string& spriteName)
            {
                Classes::SSpriteInfo* resultInfo = PLH::FnCast(o_func, cb_hook)(self, pad, sheetName, spriteName);
                if ((spriteName == "sprite_not_found" || spriteName == "texture_not_found") || (resultInfo->texture != nullptr && resultInfo->texture->texture_name != "error"))
                {
                    return resultInfo;
                }

                SheetsExtension* sheetsExt = (SheetsExtension*)ExtensionManager::GetByName("SheetsExtension");
                const std::vector<std::string>& sheetNames = sheetsExt->GetSheetNames();
                for (std::string textureName : sheetNames) {
                    resultInfo = PLH::FnCast(o_func, cb_hook)(self, pad, textureName, spriteName);

                    if (resultInfo->texture != nullptr && resultInfo->texture->texture_name != "error")
                    {
                        break;
                    }
                }
                return resultInfo;
            }

			auto GetSpriteInfoPtr::Apply() -> bool
			{
                const void* address = Signatures::GetAddressOf(Sigs::CTextureManager_GetSpriteInfoPtr);
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