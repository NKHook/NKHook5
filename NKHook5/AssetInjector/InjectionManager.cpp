#include "InjectionManager.h"

#include <filesystem>
#include <vector>
#include "HotAsset.h"

using namespace NKHook5::AssetInjector;
namespace fs = std::filesystem;

static std::vector<Asset*> hotAssets;

void InjectionManager::Initialize() {
	std::string hotSeat = "HotSeat";
	for (const fs::directory_entry& entry : fs::recursive_directory_iterator(hotSeat)) {
		if (!entry.is_directory()) {
			std::string entryStr = entry.path().string();
			entryStr.replace(entryStr.find(hotSeat), hotSeat.length()+1, "");
			while (entryStr.find("\\") != std::string::npos) {
				entryStr.replace(entryStr.find("\\"), sizeof("\\")-1, "/");
			}
			HotAsset* hotAsset = new HotAsset(entryStr);
			hotAssets.push_back(hotAsset);
			printf("Added new asset %s to hotAsset map\n", entryStr.c_str());
		}
	}
}

Asset* InjectionManager::FindInjectedAsset(std::string path)
{
	fs::path cd = fs::current_path();

	printf("Finding asset '%s'...\n", path.c_str());
	//First check HotSeat, these are development assets for mod devs
	for (const auto& asset : hotAssets) {
		printf("Checking asset '%s'\n", asset->GetPath().c_str());
		if (asset->GetPath() == path) {
			printf("Found a match for '%s' on the hotseat!\n", path.c_str());
			return asset;
		}
	}

	//Then, check mods in the user-defined order
	fs::path modsDir = cd / "Mods";
	//Finally, if the asset still isnt found, let the game handle it
	printf("Failed to find asset '%s', passing search back to the game.\n", path.c_str());
	return nullptr;
}