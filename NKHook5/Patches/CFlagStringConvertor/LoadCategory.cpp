#include "LoadCategory.h"

#include "../../Util/NewFramework.h"

#include "../../Classes/CBloonFactory.h"
#include "../../Classes/CTowerFactory.h"
#include "../../Classes/CWeaponFactory.h"
#include "../../Extensions/StatusEffect/StatusDefinitionsExt.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"

#include <Extensions/Bloon/BloonFlagsExt.h>
#include <Extensions/Tower/TowerFlagsExt.h>
#include <Extensions/Weapon/WeaponFlagsExt.h>
#include <Extensions/StatusEffect/StatusFlagsExt.h>
#include <Extensions/ExtensionManager.h>
#include <Logging/Logger.h>

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
NKHook5::Util::FlagManager g_towerFlags;
extern NKHook5::Classes::CBloonFactory* g_bloonFactory;
NKHook5::Util::FlagManager g_bloonFlags;
NKHook5::Util::FlagManager g_bloonStatusFlags;
extern NKHook5::Classes::CWeaponFactory* g_weaponFactory;
NKHook5::Util::FlagManager g_weaponFlags;


namespace NKHook5::Patches::CFlagStringConvertor
{
	using namespace Common;
	using namespace Common::Extensions;
	using namespace Common::Extensions::Bloon;
	using namespace Common::Extensions::Generic;
	using namespace Common::Extensions::StatusEffect;
	using namespace Common::Extensions::Tower;
	using namespace Common::Extensions::Weapon;
	using namespace Common::Logging::Logger;
	using namespace NKHook5;
	using namespace NKHook5::Extensions;
	using namespace NKHook5::Extensions::StatusEffect;
	using namespace Signatures;

	static uint64_t o_func;
	void* LoadCategory::cb_hook(int category, nfw::string* stringList, size_t stringCount, int indexMode) {
		auto* self = reinterpret_cast<Classes::CFlagStringConvertor*>(this);

		//Hijack and load new tower ids
		if (self == g_towerFactory) {
			if (category == 0) {
				Print(LogLevel::INFO, "Hijacking tower registration to inject new types...");
				nfw::vector<nfw::string> allTowers;
				auto* towerFlagExt = (TowerFlagExt*)ExtensionManager::GetByName("TowerFlags");
				Print(LogLevel::INFO, "Copying old types...");
				for (int i = 0; i < stringCount; i++) {
					uint64_t numericId = static_cast<uint64_t>(1) << i;
					g_towerFlags.Register(numericId, stringList[i]);
					allTowers.push_back(stringList[i]);
					Print(LogLevel::INFO, "Copied '%s' to slot '%llx'", stringList[i].c_str(), numericId);
				}
				Print(LogLevel::INFO, "Old types copied!");
				Print(LogLevel::INFO, "Injecting new types...");
				for (const std::string& flagDef : towerFlagExt->GetFlags()) {
					uint64_t moddedSlot = g_towerFlags.Register(nfw::string(flagDef));
					allTowers.emplace_back(flagDef);
					Print(LogLevel::INFO, "Injected '%s' at slot '%llx'", flagDef.c_str(), moddedSlot);
				}
				Print(LogLevel::INFO, "New types injected!");

				auto ofn = std::bit_cast<decltype(&LoadCategory::cb_hook)>(reinterpret_cast<void*>(o_func));
				return (this->*ofn)(category, allTowers.data(), allTowers.size(), indexMode);
				//return ((void*(__thiscall*)(void*, int, void*, int, int))o_func)(self, category, allTowers.data(), allTowers.size(), indexMode);
				//return PLH::FnCast(o_func, &cb_hook)(self, pad, category, towerTypes.data(), towerTypes.size(), indexMode);
			}
		}

		//Hijack bloonFactory ids
		if (self == g_bloonFactory)
		{
			//Bloon types category
			if (category == 0)
			{
				Print(LogLevel::INFO, "Hijacking bloon registration to inject new types...");
				nfw::vector<nfw::string> allBloons;
				auto* bloonFlagExt = (BloonFlagExt*)ExtensionManager::GetByName("BloonFlags");
				Print(LogLevel::INFO, "Copying old types...");
				for (int i = 0; i < stringCount; i++) {
					uint64_t numericId = static_cast<uint64_t>(1) << i;
					g_bloonFlags.Register(numericId, stringList[i]);
					allBloons.push_back(stringList[i]);
					Print(LogLevel::INFO, "Copied '%s' to slot '%llx'", stringList[i].c_str(), numericId);
				}
				Print(LogLevel::INFO, "Old types copied!");
				Print(LogLevel::INFO, "Injecting new types...");
				for (const std::string& flagDef : bloonFlagExt->GetFlags()) {
					uint64_t moddedSlot = g_bloonFlags.Register(nfw::string(flagDef));
					allBloons.emplace_back(flagDef);
					Print(LogLevel::INFO, "Injected '%s' at slot '%llx'", flagDef.c_str(), moddedSlot);
				}
				Print(LogLevel::INFO, "New types injected!");
			}
			//Status effect category
			if (category == 1)
			{
				Print(LogLevel::INFO, "Hijacking bloon status effect registration to inject new types...");
				nfw::vector<nfw::string> allEffects;
				auto* statusFlagExt = (Common::Extensions::StatusEffect::StatusFlagsExt*)ExtensionManager::GetByName("StatusFlags");
				auto* statusDefsExt = (StatusDefinitionsExt*)ExtensionManager::GetByName("StatusDefinitions");
				Print(LogLevel::INFO, "Copying old types...");
				for (int i = 0; i < stringCount; i++) {
					uint64_t numericId = static_cast<uint64_t>(1) << i;
					g_bloonStatusFlags.Register(numericId, stringList[i]);
					allEffects.emplace_back(stringList[i]);
					Print(LogLevel::INFO, "Copied '%s' to slot '%llx'", stringList[i].c_str(), numericId);
				}
				Print(LogLevel::INFO, "Old types copied!");
				Print(LogLevel::INFO, "Injecting new types...");
				for (const std::string& flagDef : statusFlagExt->GetFlags()) {
					uint64_t moddedSlot = g_bloonStatusFlags.Register(nfw::string(flagDef));
					allEffects.emplace_back(flagDef);
					Print(LogLevel::INFO, "Injected '%s' at slot '%llx'", flagDef.c_str(), moddedSlot);
				}
				Print(LogLevel::INFO, "New types injected!");

				auto ofn = std::bit_cast<decltype(&LoadCategory::cb_hook)>(reinterpret_cast<void*>(o_func));
				return (this->*ofn)(category, allEffects.data(), allEffects.size(), indexMode);
				//return ((void* (__thiscall*)(void*, int, void*, int, int))o_func)(self, category, allEffects.data(), allEffects.size(), indexMode);
			}
		}

		//Hijack weaponFactory ids
		if (self == g_weaponFactory)
		{
			//Weapon types category
			if (category == 0)
			{
				Print(LogLevel::INFO, "Hijacking weapon registration to inject new types...");
				nfw::vector<nfw::string> allWeapons;
				auto* weaponFlagExt = (WeaponFlagsExt*)ExtensionManager::GetByName("WeaponFlags");
				Print(LogLevel::INFO, "Copying old types...");
				for (int i = 0; i < stringCount; i++) {
					//We want all slots to use the custom slot system since there are more than can fit in the flag system
					uint64_t numericId = g_weaponFlags.Register(stringList[i]);
					allWeapons.push_back(stringList[i]);
					Print(LogLevel::INFO, "Copied '%s' to slot '%llx'", stringList[i].c_str(), numericId);
				}
				Print(LogLevel::INFO, "Old types copied!");
				Print(LogLevel::INFO, "Injecting new types...");
				for (const std::string& flagDef : weaponFlagExt->GetFlags()) {
					uint64_t moddedSlot = g_weaponFlags.Register(nfw::string(flagDef));
					allWeapons.emplace_back(flagDef);
					Print(LogLevel::INFO, "Injected '%s' at slot '%llx'", flagDef.c_str(), moddedSlot);
				}
				Print(LogLevel::INFO, "New types injected!");

				auto ofn = std::bit_cast<decltype(&LoadCategory::cb_hook)>(reinterpret_cast<void*>(o_func));
				return (this->*ofn)(category, allWeapons.data(), allWeapons.size(), indexMode);
			}
		}

		auto ofn = std::bit_cast<decltype(&LoadCategory::cb_hook)>(reinterpret_cast<void*>(o_func));
		return (this->*ofn)(category, stringList, stringCount, indexMode);
	}

	auto LoadCategory::Apply() -> bool
	{
		const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_LoadCategory);
		if(address)
		{
			auto* detour = new PLH::x86Detour((const uint64_t)address, std::bit_cast<size_t>(&LoadCategory::cb_hook), &o_func);
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

