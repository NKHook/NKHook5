#include "ModLoader.h"

#include "../Classes/CZipFile.h"
#include <iostream>
#include "../Mod/ModArchive.h"

using namespace NKHook5;
using namespace NKHook5::AssetInjector;
using namespace NKHook5::Mod;

void ModLoader::Initialize()
{
	ModArchive testArchive;
	testArchive.Open("Mods/BTD_Revolution.nkh");
	std::string modName = testArchive.GetInfo().name;
	if (modName.length() == 0) {
		modName = "NO NAME";
	}
	printf("Loaded mod '%s'", modName.c_str());
	std::cin.get();
}

Asset* ModLoader::FindInjectedAsset(std::string path)
{
	return nullptr;
}
