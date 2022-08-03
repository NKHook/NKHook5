#include "DiskAsset.h"

#include <fstream>

using namespace NKHook5::AssetInjector;
namespace fs = std::filesystem;

DiskAsset::DiskAsset(const std::string& assetPath, const fs::path& pathOnDisk) : Asset::Asset(assetPath) {
	this->pathOnDisk = pathOnDisk;
}

void* DiskAsset::GetAssetOnHeap() {
	if (!this->Exists()) {
		printf("Error loading asset '%s': %s\n", this->GetPathOnDisk().string().c_str(), "The asset does not exist");
		return nullptr;
	}
	try {
		//Its really allocating for the size on disk
		std::ifstream file(this->GetPathOnDisk(), std::ios::binary | std::ios::ate);
		size_t size = file.tellg();
		file.seekg(0, std::ios::beg);

		if (size == 0 || size == -1) {
			return nullptr;
		}

		this->assetHeap = malloc(size);
		file.read((char*)this->assetHeap, size);
		file.close();

		return this->assetHeap;
	}
	catch (std::exception& ex) {
		printf("Error loading asset '%s': %s\n", this->GetPathOnDisk().string().c_str(), ex.what());
	}
	return nullptr;
}

size_t DiskAsset::GetSizeOnHeap() {
	if (!this->Exists()) {
		return 0;
	}
	std::ifstream file(this->GetPathOnDisk(), std::ios::binary | std::ios::ate);
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	file.close();
	return size;
}

const fs::path& DiskAsset::GetPathOnDisk()
{
	return this->pathOnDisk;
}

bool DiskAsset::Exists()
{
	return fs::exists(this->pathOnDisk);
}
