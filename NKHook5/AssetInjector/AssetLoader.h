#pragma once
#include "Asset.h"
#include <string>
#include <vector>

namespace NKHook5 {
	namespace AssetInjector {
		class AssetLoader {
		public:
			virtual void Initialize();
			virtual std::vector<Asset*> FindInjectedAsset(std::string path);
		};
	}
}