#pragma once

#include "Asset.h"
#include "AssetSource.h"

#include <filesystem>
#include <memory>
#include <vector>

namespace NKHook5 {
	namespace Assets {
		namespace fs = std::filesystem;

		class AssetServer {
			std::vector<AssetSource*> sources;
			std::vector<std::shared_ptr<Asset>> cache;

			AssetServer() = default;
		public:
			static AssetServer* GetServer();

			virtual void AddSource(AssetSource* source);
			virtual bool Has(fs::path assetPath);
			virtual std::shared_ptr<Asset> Serve(fs::path assetPath, std::vector<uint8_t> vanilla); //Serves any file after it has been fully merged, reflected, etc

			virtual std::shared_ptr<Asset> ServeGeneric(fs::path assetPath, std::vector<uint8_t> vanilla); //Serves any file
			virtual std::shared_ptr<Asset> ServeJSON(fs::path assetPath, std::vector<uint8_t> vanilla); //Serves a merged JSON file
			virtual std::shared_ptr<Asset> ServeXML(fs::path assetPath, std::vector<uint8_t> vanilla); //Serves a reflected XML file
		};
	}
}