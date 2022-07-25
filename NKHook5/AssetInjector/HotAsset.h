#pragma once

#include "Asset.h"
#include <filesystem>

namespace NKHook5 {
	namespace AssetInjector {
		class HotAsset : public Asset {
		public:
			HotAsset(std::string relAssetPath);
		};
	}
}