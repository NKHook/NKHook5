#include "ExtensionManager.h"

#include "Generic/FlagsExtension.h"
#include "Textures/SheetsExtension.h"
#include "Tower/TowerFlagsExt.h"

using namespace Common::Extensions;

static std::vector<Extension*> extensions;

void ExtensionManager::AddAll()
{
	ExtensionManager::AddExtension(new Textures::SheetsExtension());
	ExtensionManager::AddExtension(new Tower::TowerFlagExt());
}

void ExtensionManager::AddExtension(Extension* toAdd)
{
	printf("Adding extension '%s' for target '%s'\n", toAdd->GetName().c_str(), toAdd->GetTarget().c_str());
	if (GetByName(toAdd->GetName())) {
		printf("Cannot add extension '%s', the name is not unique!\n", toAdd->GetName().c_str());
	}
	extensions.push_back(toAdd);
	printf("Added!\n");
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
