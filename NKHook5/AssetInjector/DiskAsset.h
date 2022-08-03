#pragma once

#include "Asset.h"
#include <filesystem>

namespace NKHook5 {
	namespace AssetInjector {
		class DiskAsset : public Asset {
		private:
			std::filesystem::path pathOnDisk;
		public:
			DiskAsset(const std::string& assetPath, const std::filesystem::path& pathOnDisk);
			virtual void* GetAssetOnHeap();
			virtual size_t GetSizeOnHeap();
			virtual const std::filesystem::path& GetPathOnDisk();
			virtual bool Exists();
		};
	}
}