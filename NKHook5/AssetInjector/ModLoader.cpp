#include "ModLoader.h"

#include "../Classes/CZipFile.h"
#include <iostream>
#undef min
#undef max
#include <ZipFile.h>
#include <ZipArchive.h>

using namespace NKHook5;
using namespace NKHook5::AssetInjector;

void ModLoader::Initialize()
{
	ZipArchive::Ptr modArchive = ZipFile::Open("Mods/BTD_Revolution.nkh");
	ZipArchiveEntry::Ptr modInfoEntry = modArchive->GetEntry("modinfo.json");
	std::istream* stream = modInfoEntry->GetDecompressionStream();
	std::string entryData(std::istreambuf_iterator<char>(*stream), {});
	printf("%s\n", entryData.c_str());
	std::cin.get();
}

Asset* ModLoader::FindInjectedAsset(std::string path)
{
	return nullptr;
}
