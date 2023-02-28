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

static std::vector<Extension*> extensions;

void ExtensionManager::AddAll()
{
	ExtensionManager::AddExtension(new Bloon::BloonFlagExt());
	ExtensionManager::AddExtension(new Generic::MergeIgnoreExtension());
	ExtensionManager::AddExtension(new StatusEffect::StatusFlagsExt());
	ExtensionManager::AddExtension(new Textures::SheetsExtension());
	ExtensionManager::AddExtension(new Tower::TowerFlagExt());
	ExtensionManager::AddExtension(new Weapon::WeaponFlagsExt());
}

void ExtensionManager::AddExtension(Extension* toAdd)
{
	Print(LogLevel::INFO, "Adding extension '%s' for target '%s'", toAdd->GetName().c_str(), toAdd->GetTarget().c_str());
	if (GetByName(toAdd->GetName())) {
		Print(LogLevel::ERR, "Cannot add extension '%s', the name is not unique!", toAdd->GetName().c_str());
	}
	extensions.push_back(toAdd);
	Print(LogLevel::INFO, "Added!");
}

Extension* ExtensionManager::GetByName(std::string name) {
	for (Extension* extension : extensions) {
		if (extension->GetName() == name) {
			return extension;
		}
	}
	return nullptr;
}

std::vector<Extension*> ExtensionManager::GetByTarget(std::string target)
{
	std::vector<Extension*> results;
	for (Extension* extension : extensions) {
		if (extension->GetTarget() == target) {
			results.push_back(extension);
		}
	}
	return results;
}

std::vector<Extension*> ExtensionManager::GetCustomDocuments()
{
	std::vector<Extension*> results;
	for (Extension* extension : extensions) {
		if (extension->IsCustomDocument()) {
			results.push_back(extension);
		}
	}
	return results;
}
