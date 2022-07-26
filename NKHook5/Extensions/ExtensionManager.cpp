#include "ExtensionManager.h"

#include "Generic/FlagsExtension.h"
#include "Tower/TowerFlagsExt.h"

using namespace NKHook5::Extensions;

static std::vector<Extension*> extensions;

void ExtensionManager::AddAll()
{
	ExtensionManager::AddExtension(new Tower::TowerFlagExt());
}

void ExtensionManager::AddExtension(Extension* toAdd)
{
	printf("Adding extension for target '%s'\n", toAdd->GetTarget().c_str());
	extensions.push_back(toAdd);
	printf("Added!\n");
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
