#include "ModLoader.h"

#include "../Classes/CZipFile.h"
#include "../Mod/ModArchive.h"
#include "../Util/Json/MergedDocument.h"
#include <filesystem>
#include <iostream>
#include "ModdedAsset.h"

using namespace NKHook5;
using namespace NKHook5::AssetInjector;
using namespace NKHook5::Classes;
using namespace NKHook5::Mod;
using namespace NKHook5::Signatures;
using namespace NKHook5::Util;
using namespace NKHook5::Util::Json;
namespace fs = std::filesystem;

static std::vector<ModArchive*> loadedMods;
static std::vector<ModdedAsset*> finalAssets;

void ModLoader::Initialize()
{
	if (fs::exists("Mods") && fs::is_directory("Mods")) {
		for (const auto& file : fs::directory_iterator("Mods")) {
			if (!file.is_directory()) {
				ModArchive* modFile = new ModArchive();
				if (modFile->Open(file)) {
					loadedMods.push_back(modFile);
					printf("Loading %s...\n", modFile->GetInfo().name.c_str());
				}
				else
					printf("Failed to open mod file: %s\n", file.path().string().c_str());
			}
		}
	}
	else {
		printf("CANNOT LOAD MODS! The ./Mods directory is missing!\n");
	}

	for (const ModArchive* mod : loadedMods) {
		const std::vector<std::string>& entryPaths = mod->GetEntries();
		for (auto& entryPath : entryPaths) {
			std::string entryContent;
			if (mod->ReadEntry(entryPath, &entryContent)) {
				ModdedAsset* desiredAsset = nullptr;
				for (ModdedAsset* asset : finalAssets) {
					if (asset->GetPath() == entryPath) {
						desiredAsset = asset;
						break;
					}
				}
				if (desiredAsset == nullptr) {
					desiredAsset = new ModdedAsset(entryPath);
					finalAssets.push_back(desiredAsset);
				}

				try {
					std::string assetStr = std::string((char*)desiredAsset->GetAssetOnHeap(), desiredAsset->GetSizeOnHeap());

					nlohmann::ordered_json assetJson = nlohmann::ordered_json::parse(assetStr);
					nlohmann::ordered_json entryJson = nlohmann::ordered_json::parse(entryContent);

					MergedDocument merger;
					merger.Add(assetJson);
					merger.Add(entryJson);
					std::string merged = merger.GetMerged().dump();

					desiredAsset->AllocateFor(merged.size());
					memcpy_s(desiredAsset->GetAssetOnHeap(), merged.size(), merged.data(), merged.size());
				}
				catch (std::exception& ex) {
					printf("Error whilst merging asset '%s'\n", ex.what());
					printf("Overwriting with the newest asset\n");
					desiredAsset->AllocateFor(entryContent.size());
					memcpy_s(desiredAsset->GetAssetOnHeap(), entryContent.size(), entryContent.data(), entryContent.size());
				}
			}
		}
	}
}

Asset* ModLoader::FindInjectedAsset(std::string path)
{
	for (ModdedAsset* asset : finalAssets) {
		if (asset->GetPath() == path) {
			return asset;
		}
	}
	return nullptr;
}
