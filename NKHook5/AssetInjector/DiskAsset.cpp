#include "DiskAsset.h"

#include <fstream>

using namespace NKHook5::AssetInjector;
namespace fs = std::filesystem;

DiskAsset::DiskAsset(const std::string& assetPath, const std::string& pathOnDisk) : Asset::Asset(assetPath) {
	this->pathOnDisk = pathOnDisk;
}

void* DiskAsset::GetAssetOnHeap() {
	if (!this->Exists()) {
		printf("Error loading asset '%s': %s", this->GetPathOnDisk().c_str(), "The asset does not exist");
		return nullptr;
	}
	try {
		//Its really allocating for the size on disk
		size_t length = this->GetSizeOnHeap();
		this->AllocateFor(length);

		std::ifstream in(this->GetPathOnDisk(), std::ifstream::ate | std::ifstream::binary);
		this->assetHeap = malloc(length + 1);
		in.read((char*)this->assetHeap, length);

		return this->assetHeap;
	}
	catch (std::exception& ex) {
		printf("Error loading asset '%s': %s", this->GetPathOnDisk().c_str(), ex.what());
	}
	return nullptr;
}

size_t DiskAsset::GetSizeOnHeap() {
	std::ifstream in(this->GetPathOnDisk(), std::ifstream::ate | std::ifstream::binary);
	in.seekg(0, std::ios::end);
	size_t length = in.tellg();
	in.seekg(0, std::ios::beg);
	in.close();
	return length;
}

const std::string& DiskAsset::GetPathOnDisk()
{
	return this->pathOnDisk;
}

bool DiskAsset::Exists()
{
	return fs::exists(this->pathOnDisk);
}
