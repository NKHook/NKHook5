#include "ModdedAsset.h"

using namespace NKHook5::AssetInjector;

ModdedAsset::ModdedAsset(std::string path) : MemAsset(path)
{
}

bool ModdedAsset::ExpectsMerge()
{
	return true;
}
