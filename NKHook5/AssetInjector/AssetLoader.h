#pragma once
#include "Asset.h"
#include <string>

namespace NKHook5 {
	namespace AssetInjector {
		class AssetLoader {
		public:
			virtual void Initialize();
			virtual Asset* FindInjectedAsset(std::string path);
		};
	}
}