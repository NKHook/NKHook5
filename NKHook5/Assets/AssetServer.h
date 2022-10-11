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

			AssetServer() = default;
		public:
			static AssetServer* GetServer();

			virtual void AddSource(AssetSource* source);
			virtual std::shared_ptr<Asset> Serve(fs::path assetPath); //Serves any file after it has been fully merged, reflected, etc

			virtual std::shared_ptr<Asset> ServeGeneric(fs::path assetPath); //Serves any file
			virtual std::shared_ptr<Asset> ServeJSON(fs::path assetPath); //Serves a merged JSON file
			virtual std::shared_ptr<Asset> ServeXML(fs::path assetPath); //Serves a reflected XML file
		};
	}
}