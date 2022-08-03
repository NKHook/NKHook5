#pragma once

#include "Asset.h"
#include <filesystem>

namespace NKHook5 {
	namespace AssetInjector {
		class DiskAsset : public Asset {
		private:
			std::string pathOnDisk;
		public:
			DiskAsset(const std::string& assetPath, const std::string& pathOnDisk);
			virtual void* GetAssetOnHeap();
			virtual size_t GetSizeOnHeap();
			virtual const std::string& GetPathOnDisk();
			virtual bool Exists();
		};
	}
}