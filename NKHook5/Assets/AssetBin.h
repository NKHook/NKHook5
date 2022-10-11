#pragma once

#include <string>

namespace NKHook5 {
	namespace Assets {
		enum class AssetBin {
			INVALID,
			AUDIO,
			FONTS,
			JSON,
			LOC,
			SCRIPTS,
			SHADERS,
			TEXTURES,
			BIN_COUNT
		};
		static constexpr const char* BinNames[] = {
			"Invalid",
			"Audio",
			"Fonts",
			"JSON",
			"Loc",
			"Scripts",
			"Shaders",
			"Textures",
			"Invalid" //Another invalid for BIN_COUNT
		};

		AssetBin FromString(std::string binName);
		std::string ToString(AssetBin bin);
	}
}