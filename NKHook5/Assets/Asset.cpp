#include "Asset.h"

using namespace NKHook5;
using namespace NKHook5::Assets;

AssetBin FromPath(fs::path assetPath) {
	if (assetPath.string().find("Assets/") == 0) {
		assetPath = assetPath.string().substr(sizeof("Assets/") - 1);
		size_t slashPos = assetPath.string().find("/");
		std::string binName = assetPath.string().substr(slashPos);
		return FromString(binName);
	}
	return AssetBin::INVALID;
}

Asset::Asset(fs::path assetPath)
{
	this->assetBin = FromPath(assetPath);
	this->assetPath = assetPath;
}

Asset::Asset(fs::path assetPath, std::vector<uint8_t> assetData)
{
	this->assetBin = FromPath(assetPath);
	this->assetPath = assetPath;
	this->assetData = assetData;
}

const AssetBin& Asset::GetBin()
{
	return this->assetBin;
}

const fs::path& Asset::GetRelPath()
{
	return this->assetPath;
}

fs::path Asset::GetFullPath()
{
	fs::path result = "Assets";
	result /= ToString(this->GetBin());
	result /= this->GetRelPath();
	return result;
}

std::vector<uint8_t> Asset::GetData()
{
	return this->assetData;
}
