#include "Asset.h"

using namespace NKHook5::AssetInjector;

Asset::Asset() {
	this->assetPath = "";
	this->assetHeap = nullptr;
	this->heapSize = 0;
}

Asset::Asset(const std::string& assetPath) : Asset::Asset() {
	this->assetPath = assetPath;
}

void Asset::AllocateFor(size_t assetSize) {
	if (this->assetHeap != nullptr) {
		free(this->assetHeap);
	}
	this->assetHeap = malloc(assetSize);
	this->heapSize = assetSize;
}

void* Asset::GetAssetOnHeap() {
	return this->assetHeap;
}

size_t Asset::GetSizeOnHeap() {
	return this->heapSize;
}

const std::string& Asset::GetPath()
{
	return this->assetPath;
}
