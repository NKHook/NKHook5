#include "AssetSource.h"

using namespace NKHook5;
using namespace NKHook5::Assets;
namespace fs = std::filesystem;

AssetSource::AssetSource(std::string sourceName) {
	this->sourceName = sourceName;
}

std::shared_ptr<Asset> Find(fs::path assetPath) {
	return nullptr;
}

std::shared_ptr<Asset> FindRel(AssetBin bin, fs::path relativePath) {
	return nullptr;
}

std::shared_ptr<Asset> FindInBin(AssetBin bin, std::string filename) {
	return nullptr;
}