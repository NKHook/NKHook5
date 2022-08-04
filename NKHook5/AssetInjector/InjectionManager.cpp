#include "InjectionManager.h"

#include <filesystem>
#include <vector>
#include "MemAsset.h"
#include "AssetLoader.h"
#include "ModLoader.h"
#include "TestModAssetLoader.h"

using namespace NKHook5::AssetInjector;
namespace fs = std::filesystem;

static AssetLoader* currentLoader;

//From main.cpp
extern std::string* testModDir;

void InjectionManager::SetupAssetLoader() {
	if (testModDir != nullptr) {
		currentLoader = new TestModAssetLoader(*testModDir);
	}
	else {
		currentLoader = new ModLoader();
	}
	currentLoader->Initialize();
}

AssetLoader* InjectionManager::GetLoader()
{
	return currentLoader;
}
