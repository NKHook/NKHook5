#include "TestModAssetLoader.h"

#include "DiskAsset.h"
#include "MemAsset.h"
#include "../Util/Json/MergedDocument.h"

using namespace NKHook5::AssetInjector;
using namespace NKHook5::Util::Json;
namespace fs = std::filesystem;

TestModAssetLoader::TestModAssetLoader(const std::string& modDir)
{
	this->modDir = modDir;
}

void TestModAssetLoader::Initialize()
{
}

Asset* TestModAssetLoader::FindInjectedAsset(std::string path)
{
	try {
		std::string normalPath;
		if (path.find("./Assets/") != std::string::npos) {
			normalPath = path.replace(0, sizeof("./Assets") - 1, "");
		}
		else if(path.find("/Assets/") != std::string::npos) {
			normalPath = path.replace(0, sizeof("/Assets") - 1, "");
		}
		fs::path vanillaPath = fs::path(this->modDir) / "Vanilla" / normalPath;
		fs::path modPath = fs::path(this->modDir) / "Mod" / normalPath;

		DiskAsset* vanillaAsset = new DiskAsset(path, vanillaPath.string());
		DiskAsset* modAsset = new DiskAsset(path, modPath.string());

		void* vanillaData = vanillaAsset->GetAssetOnHeap();
		void* modData = modAsset->GetAssetOnHeap();
		if (vanillaData != nullptr) {
			if (modData != nullptr) {
				std::string vanillaString = std::string((char*)vanillaAsset->GetAssetOnHeap(), vanillaAsset->GetSizeOnHeap());
				std::string modString = std::string((char*)modAsset->GetAssetOnHeap(), modAsset->GetSizeOnHeap());

				nlohmann::json vanillaJson = nlohmann::json::parse(vanillaString);
				nlohmann::json modJson = nlohmann::json::parse(modString);

				MergedDocument merged;
				merged.Add(vanillaJson);
				merged.Add(modJson);
				nlohmann::json mergedJson = merged.GetMerged();
				std::string mergedString = mergedJson.dump();

				MemAsset* memAsset = new MemAsset(path);
				memAsset->AllocateFor(mergedString.size());
				memcpy(memAsset->GetAssetOnHeap(), mergedString.data(), mergedString.size());

				vanillaAsset->Release();
				modAsset->Release();

				delete vanillaAsset;
				delete modAsset;

				return memAsset;
			}
			else {
				delete modAsset;
				return vanillaAsset;
			}
		}
	}
	catch (std::exception& ex) {
		printf("Error getting injected asset: %s\n", ex.what());
	}

	return nullptr;
}
