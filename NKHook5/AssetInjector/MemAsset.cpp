#include "MemAsset.h"

#include <fstream>

using namespace NKHook5::AssetInjector;
namespace fs = std::filesystem;

MemAsset::MemAsset(std::string relAssetPath) : Asset(relAssetPath) {

	fs::path cd = fs::current_path();
	fs::path hotdir = cd / "HotSeat";
	fs::path assetFile = hotdir / relAssetPath;
	if (fs::exists(assetFile)) {
		std::ifstream file(assetFile, std::ios::binary | std::ios::ate);
		size_t size = file.tellg();
		file.seekg(0, std::ios::beg);

		this->AllocateFor(size);
		void* buffer = this->GetAssetOnHeap();
		file.read((char*)buffer, size);
	}
}

void MemAsset::Release()
{
	return;
}
