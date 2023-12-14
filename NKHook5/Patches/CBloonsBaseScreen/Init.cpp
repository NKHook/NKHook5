#include "Init.h"

#include "../../Assets/Asset.h"
#include "../../Assets/AssetServer.h"
#include "../../Classes/CGameScreen.h"
#include "../../Signatures/Signature.h"

#include <Extensions/Textures/SheetsExtension.h>
#include <Extensions/ExtensionManager.h>

namespace NKHook5::Patches::CBloonsBaseScreen
{
	using namespace Common;
	using namespace Common::Extensions;
	using namespace Common::Extensions::Textures;
	using namespace NKHook5;
	using namespace NKHook5::Assets;
	using namespace NKHook5::Patches;
	using namespace NKHook5::Signatures;

	static uint64_t o_func;
	void Init::cb_hook(Classes::IScreenData* pScreenData) {
		auto* self = reinterpret_cast<Classes::CGameScreen*>(this);

		auto ofn = std::bit_cast<decltype(&Init::cb_hook)>(reinterpret_cast<void*>(o_func));
		(this->*ofn)(pScreenData);

		auto* sheetsExt = dynamic_cast<SheetsExtension*>(ExtensionManager::GetByName("SheetsExtension"));
		const std::vector<std::string>& sheetNames = sheetsExt->GetSheetNames();
		for (const auto& textureName : sheetNames) {
			nfw::string nfwName(textureName);
			self->StartUsingAsset(Classes::CAssetBag::eAssetType::TEXTURE, nfwName);
		}
	}

	auto Init::Apply() -> bool
	{
		const void* address = Signatures::GetAddressOf(Sigs::CGameScreen_Init);
		if(address)
		{
			auto* detour = new PLH::x86Detour((const uintptr_t)address, std::bit_cast<size_t>(&Init::cb_hook), &o_func);
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
} // namespace CGameScreen