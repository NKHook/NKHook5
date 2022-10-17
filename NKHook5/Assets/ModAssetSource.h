#pragma once

#include "AssetSource.h"

#include <Files/ModArchive.h>

#include <filesystem>

namespace NKHook5 {
	namespace Assets {
		using namespace Common;
		using namespace Common::Files;
		using namespace Common::Mod;

		class ModAssetSource : public AssetSource {
			std::shared_ptr<ModArchive> modArch;
		public:
			ModAssetSource(std::filesystem::path modPath);

			virtual bool Has(fs::path assetPath);
			virtual std::shared_ptr<Asset> Find(fs::path assetPath) override;
			virtual std::shared_ptr<Asset> FindRel(AssetBin bin, fs::path relativePath) override;
			virtual std::shared_ptr<Asset> FindInBin(AssetBin bin, std::string filename) override;
		};
	}
}