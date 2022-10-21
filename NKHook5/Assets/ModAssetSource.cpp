#include "ModAssetSource.h"

using namespace Common;
using namespace Common::Files;
using namespace Common::Mod;
using namespace NKHook5;
using namespace NKHook5::Assets;
namespace fs = std::filesystem;

ModAssetSource::ModAssetSource(fs::path modPath) : AssetSource(modPath.stem().string())
{
	this->modArch = std::make_shared<ModArchive>();
	if (!this->modArch->OpenRead(modPath)) {
		throw std::exception((std::string("Failed to read mod file: ") + modPath.string()).c_str());
	}
}

const std::shared_ptr<ModArchive>& ModAssetSource::GetModArch()
{
	return this->modArch;
}

bool ModAssetSource::Has(fs::path assetPath)
{
	return this->modArch->HasEntry(assetPath.string());
}

std::shared_ptr<Asset> ModAssetSource::Find(fs::path assetPath)
{
	const std::vector<uint8_t>& entryData = this->modArch->ReadEntry(assetPath.string());
	if (entryData.empty())
		return nullptr;
	return std::make_shared<Asset>(assetPath, entryData);
}

std::shared_ptr<Asset> ModAssetSource::FindRel(AssetBin bin, fs::path relativePath)
{
	std::string binDir = ToString(bin);
	fs::path lookupPath = "Assets/";
	lookupPath /= binDir;
	lookupPath /= relativePath;
	return this->Find(lookupPath);
}

std::shared_ptr<Asset> ModAssetSource::FindInBin(AssetBin bin, std::string filename)
{
	std::string binDir = ToString(bin);
	for (const auto& entry : this->modArch->GetEntries()) {
		fs::path entryPath = entry.substr(sizeof("Assets/") - 1);
		if (entryPath.string().find(binDir) == 0) {
			if (entryPath.filename() == filename || entryPath.stem() == filename) {
				return this->Find(entry);
			}
		}
	}
	return nullptr;
}
