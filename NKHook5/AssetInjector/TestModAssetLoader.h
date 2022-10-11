#pragma once

#include "AssetLoader.h"

namespace NKHook5 {
	namespace AssetInjector {
		class TestModAssetLoader : public AssetLoader {
			std::string modDir;
		public:
			TestModAssetLoader(const std::string& modDir);
			virtual void Initialize();
			virtual std::vector<Asset*> FindInjectedAsset(std::string path);
		};
	}
}