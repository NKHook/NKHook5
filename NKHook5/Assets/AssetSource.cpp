#include "AssetSource.h"

using namespace NKHook5;
using namespace NKHook5::Assets;
namespace fs = std::filesystem;

AssetSource::AssetSource(std::string sourceName) {
	this->sourceName = sourceName;
}

std::shared_ptr<Asset> AssetSource::Find(fs::path assetPath) {
	return nullptr;
}

std::shared_ptr<Asset> AssetSource::FindRel(AssetBin bin, fs::path relativePath) {
	return nullptr;
}

std::shared_ptr<Asset> AssetSource::FindInBin(AssetBin bin, std::string filename) {
	return nullptr;
}