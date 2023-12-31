#include "Fire.h"

#include "../../Classes/CApplyStatusEffectTask.h"
#include "../../Classes/CBloon.h"
#include "../../Classes/CBloonFactory.h"
#include "../../ClassesEx/CInjectedStatusEffect.h"
#include "../../Extensions/StatusEffect/StatusDefinitionsExt.h"
#include "../../Signatures/Signature.h"
#include "../../Util/NewFramework.h"
#include "../../Util/FlagManager.h"

#include <Extensions/ExtensionManager.h>
#include <Logging/Logger.h>

extern NKHook5::Classes::CBloonFactory* g_bloonFactory;
extern NKHook5::Util::FlagManager g_bloonStatusFlags;

namespace NKHook5::Patches::CApplyStatusEffectTask
{
	using namespace Common;
	using namespace Common::Extensions;
	using namespace Common::Logging::Logger;
	using namespace NKHook5;
	using namespace NKHook5::Extensions;
	using namespace NKHook5::Extensions::StatusEffect;
	using namespace NKHook5::Patches;
	using namespace NKHook5::Signatures;

	static uint64_t o_func = 0;
	void Fire::cb_hook(Classes::CBloon* bloon, float unk, float unk2, float unk3, float unk4)
	{
		auto* task = reinterpret_cast<Classes::CApplyStatusEffectTask*>(this);

		if (NKHook5::Util::FlagManager::IsVanilla(task->effectId))
		{
			auto ofn = std::bit_cast<decltype(&Fire::cb_hook)>(reinterpret_cast<void*>(o_func));
			return (this->*ofn)(bloon, unk, unk2, unk3, unk4);
		}
		else {
			auto* statusDefs = ExtensionManager::Get<StatusDefinitionsExt>();
			const StatusDefinition* def = nullptr;
			for (const auto& definition : statusDefs->GetDefinitions())
			{
				if (task->effectId == g_bloonStatusFlags.GetFlag(definition.type))
				{
					def = &definition;
					break;
				}
			}
			if (def == nullptr)
			{
				Print(LogLevel::ERR, "Failed to find a status effect with an ID of %llx", task->effectId);
				return;
			}
			auto* effect = new ClassesEx::CInjectedStatusEffect(task->effectId, def->spriteInfo, def->texture, def->exceptMoab, task->gamePtrs->mTextureManager, false, 0.2, 1.0);
			if(task->tower)
				effect->IncTowerRef(task->tower);
			bloon->ApplyEffect(effect, !def->exceptMoab);
		}
	}

	bool Fire::Apply()
	{
		const void* address = Signatures::GetAddressOf(Sigs::CApplyStatusEffectTask_Fire);
		if (address)
		{
			auto* detour = new PLH::x86Detour((const uintptr_t)address, std::bit_cast<size_t>(&Fire::cb_hook), &o_func);
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