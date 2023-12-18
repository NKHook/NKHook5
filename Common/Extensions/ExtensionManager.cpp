#include "ExtensionManager.h"

#include "Bloon/BloonFlagsExt.h"
#include "Generic/FlagsExtension.h"
#include "Generic/MergeIgnoreExtension.h"
#include "StatusEffect/StatusFlagsExt.h"
#include "Textures/SheetsExtension.h"
#include "Tower/TowerFlagsExt.h"
#include "StatusEffect/StatusFlagsExt.h"
#include "Weapon/WeaponFlagsExt.h"

#include <Logging/Logger.h>

using namespace Common::Extensions;
using namespace Common::Logging::Logger;

void ExtensionManager::AddAll()
{
	ExtensionManager::AddExtension<Bloon::BloonFlagExt>();
	ExtensionManager::AddExtension<Generic::MergeIgnoreExtension>();
	ExtensionManager::AddExtension<StatusEffect::StatusFlagsExt>();
	ExtensionManager::AddExtension<Textures::SheetsExtension>();
	ExtensionManager::AddExtension<Tower::TowerFlagExt>();
	ExtensionManager::AddExtension<Weapon::WeaponFlagsExt>();
}

Extension* ExtensionManager::GetByName(const std::string& name) {
	for (auto** storage : storages) {
		auto* extension = *storage;
		if (extension->GetName() == name) {
			return extension;
		}
	}
	return nullptr;
}

std::vector<Extension*> ExtensionManager::GetByTarget(const std::string& target)
{
	std::vector<Extension*> results;
	for (auto** storage : storages) {
		auto* extension = *storage;
		if (extension->GetTarget() == target) {
			results.push_back(extension);
		}
	}
	return results;
}

std::vector<Extension*> ExtensionManager::GetCustomDocuments()
{
	std::vector<Extension*> results;
	for (auto** storage : storages) {
		auto* extension = *storage;
		if (extension->IsCustomDocument()) {
			results.push_back(extension);
		}
	}
	return results;
}
