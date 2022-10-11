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

std::string NKHook5::Assets::ToString(AssetBin bin) {
	std::string result = "Invalid";
	if (bin <= AssetBin::BIN_COUNT && bin >= AssetBin::INVALID) {
		result = BinNames[(size_t)bin];
	}
	return result;
}