#include "ExtensionManager.h"

#include <vector>

using namespace NKHook5::Extensions;

static std::vector<Extension*> extensions;

void ExtensionManager::AddAll()
{

}

void ExtensionManager::AddExtension(Extension* toAdd)
{
	extensions.push_back(toAdd);
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
