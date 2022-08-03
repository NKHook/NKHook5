#pragma once

#include "Asset.h"
#include <filesystem>

namespace NKHook5 {
	namespace AssetInjector {
		class MemAsset : public Asset {
		public:
			MemAsset(std::string relAssetPath);
			virtual void Release();
		};
	}
}