#pragma once

#include "Asset.h"

#include <filesystem>
#include <memory>
#include <string>

namespace NKHook5 {
	namespace Assets {
		namespace fs = std::filesystem;

		class AssetSource {
			std::string sourceName;
		public:
			AssetSource(std::string sourceName);

			virtual bool Has(fs::path assetPath);
			virtual std::shared_ptr<Asset> Find(fs::path assetPath);
			virtual std::shared_ptr<Asset> FindRel(AssetBin bin, fs::path relativePath);
			virtual std::shared_ptr<Asset> FindInBin(AssetBin bin, std::string filename);
		};
	}
}