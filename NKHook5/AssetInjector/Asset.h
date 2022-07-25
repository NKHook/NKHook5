#pragma once

#include <filesystem>

namespace NKHook5 {
	namespace AssetInjector {
		class Asset {
		private:
			std::string assetPath = "";
			void* assetHeap = nullptr;
			size_t heapSize = 0;
		public:
			Asset();
			Asset(const std::string& assetPath);
			void AllocateFor(size_t assetSize);
			virtual void* GetAssetOnHeap();
			virtual size_t GetSizeOnHeap();
			virtual const std::string& GetPath();
		};
	}
}