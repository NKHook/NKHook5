#include "ModLoader.h"

#include "ModdedAsset.h"
#include "../Classes/CZipFile.h"

#include <filesystem>
#include <iostream>
#include <Files/ModArchive.h>
#include <Util/Json/MergedDocument.h>
#include <Logging/Logger.h>

using namespace NKHook5;
using namespace NKHook5::AssetInjector;
using namespace NKHook5::Classes;
using namespace NKHook5::Signatures;
using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util;
using namespace Common::Util::Json;
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
					printf("Loading %s...\n", modFile->GetInfo().GetName().c_str());
				}
				else
					printf("Failed to open mod file: %s\n", file.path().string().c_str());
			}
		}
	}
	else {
		printf("CANNOT LOAD MODS! The ./Mods directory is missing!\n");
	}

	for (ModArchive* mod : loadedMods) {
		const std::vector<std::string>& entryPaths = mod->GetEntries();
		for (auto& entryPath : entryPaths) {
			if (entryPath.find("Assets/JSON/") == 0) {
				std::vector<uint8_t> entryBytes = mod->ReadEntry(entryPath);
				std::string entryContent = std::string(reinterpret_cast<char*>(entryBytes.data()), entryBytes.size());
				if (!entryContent.empty()) {
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

						nlohmann::ordered_json assetJson = nlohmann::ordered_json::parse(assetStr, nullptr, true, true);
						nlohmann::ordered_json entryJson = nlohmann::ordered_json::parse(entryContent, nullptr, true, true);

						MergedDocument merger;
						merger.Add(assetJson);
						merger.Add(entryJson);
						std::string merged = merger.GetMerged().dump();

						desiredAsset->AllocateFor(merged.size());
						memcpy_s(desiredAsset->GetAssetOnHeap(), merged.size(), merged.data(), merged.size());
					}
					catch (std::exception& ex) {
						//printf("Error whilst merging asset '%s'\n", ex.what());
						//printf("Overwriting with the newest asset\n");
						desiredAsset->AllocateFor(entryContent.size());
						memcpy_s(desiredAsset->GetAssetOnHeap(), entryContent.size(), entryContent.data(), entryContent.size());
					}
				}
			}
			if (entryPath.find("Assets/Textures/") == 0) {
				std::string relPath = entryPath.substr(sizeof("Assets/Textures/")-1);
				if (relPath.find(".rxml") != std::string::npos) {
					std::vector<uint8_t> patchData = mod->ReadEntry(entryPath);

					ModdedAsset* patchAsset = new ModdedAsset(entryPath);
					patchAsset->AllocateFor(patchData.size());
					memcpy_s(patchAsset->GetAssetOnHeap(), patchData.size(), patchData.data(), patchData.size());
					finalAssets.push_back(patchAsset);
				}
			}
		}
	}
}

std::vector<Asset*> ModLoader::FindInjectedAsset(std::string path)
{
	std::vector<Asset*> foundAssets;
	for (ModdedAsset* asset : finalAssets) {
		if (asset->GetPath() == path) {
			foundAssets.push_back(asset);
		}
	}
	return foundAssets;
}
