#pragma once

#include "AssetBin.h"

#include <filesystem>
#include <stdint.h>
#include <vector>

namespace NKHook5 {
	namespace Assets {
		namespace fs = std::filesystem;
		
		class Asset {
			AssetBin assetBin = AssetBin::INVALID; //The asset bin decides the "Assets/XYZ/" prefix
			fs::path assetPath; //Does not include "Assets/XYZ/" only the relative path
			std::vector<uint8_t> assetData; //THe actual content
		public:
			Asset(fs::path assetPath);
			Asset(fs::path assetPath, std::vector<uint8_t> assetData);

			virtual const AssetBin& GetBin();
			virtual const fs::path& GetRelPath();
			virtual fs::path GetFullPath();
			virtual std::vector<uint8_t> GetData();
		};
	}
}