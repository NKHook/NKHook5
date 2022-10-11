#include "AssetLoader.h"
#include "MemAsset.h"

using namespace NKHook5::AssetInjector;
namespace fs = std::filesystem;
static std::vector<Asset*> hotAssets;

void AssetLoader::Initialize()
{
	fs::path hotSeat = fs::current_path() / "HotSeat";
	if (fs::exists(hotSeat)) {
		for (const fs::directory_entry& entry : fs::recursive_directory_iterator(hotSeat)) {
			if (!entry.is_directory()) {
				std::string entryStr = entry.path().string();
				entryStr.replace(entryStr.find(hotSeat.string()), hotSeat.string().length() + 1, "");
				while (entryStr.find("\\") != std::string::npos) {
					entryStr.replace(entryStr.find("\\"), sizeof("\\") - 1, "/");
				}
				Asset* hotAsset = new MemAsset(entryStr);
				hotAssets.push_back(hotAsset);
				printf("Added new asset %s to hotAsset map\n", entryStr.c_str());
			}
		}
	}
}

std::vector<Asset*> AssetLoader::FindInjectedAsset(std::string path)
{
	std::vector<Asset*> foundAssets;
	fs::path cd = fs::current_path();

	printf("Finding asset '%s'...\n", path.c_str());
	//First check HotSeat, these are development assets for mod devs
	for (const auto& asset : hotAssets) {
		//printf("Checking asset '%s'\n", asset->GetPath().c_str());
		if (asset->GetPath() == path) {
			printf("Found a match for '%s' on the hotseat!\n", path.c_str());
			foundAssets.push_back(asset);
		}
	}

	//Then, check mods in the user-defined order
	fs::path modsDir = cd / "Mods";
	//Finally, if the asset still isnt found, let the game handle it
	//printf("Failed to find asset '%s', passing search back to the game.\n", path.c_str());
	return foundAssets;
}
