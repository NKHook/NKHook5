#include "AssetBin.h"

using namespace NKHook5;
using namespace NKHook5::Assets;

AssetBin NKHook5::Assets::FromString(std::string binName) {
	AssetBin result = AssetBin::INVALID;
	size_t idx = 0;
	for (const char* cname : BinNames) {
		if (binName == cname) {
			result = (AssetBin)idx;
			break;
		}
		idx++;
	}
	return result;
}

AssetBin NKHook5::Assets::FromPath(fs::path assetPath) {
	if (assetPath.string().find("Assets/") == 0) {
		assetPath = assetPath.string().substr(sizeof("Assets/") - 1);
		size_t slashPos = assetPath.string().find("/");
		std::string binName = assetPath.string().substr(0, slashPos);
		return FromString(binName);
	}
	return AssetBin::INVALID;
}

std::string NKHook5::Assets::ToString(AssetBin bin) {
	std::string result = "Invalid";
	if (bin <= AssetBin::BIN_COUNT && bin >= AssetBin::INVALID) {
		result = BinNames[(size_t)bin];
	}
	return result;
}