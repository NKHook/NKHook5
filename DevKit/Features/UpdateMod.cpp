#include "UpdateMod.h"

#include "../Settings.h"
#include "../Proj/Project.h"

#include <Files/File.h>
#include <Files/JetFile.h>

#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace Common::Mod;
using namespace DevKit;
using namespace DevKit::Features;
using namespace DevKit::Proj;
namespace fs = std::filesystem;

UpdateMod::UpdateMod() : Feature("update_mod", "Updates the assets of a specified mod") {

}

std::string UpdateMod::ActivatorArgs()
{
	return "-u, --update-mod";
}

void UpdateMod::Run(std::vector<std::string> args) {
	std::string modName = args[0];
	printf("Updating vanilla assets for '%s'...\n", modName.c_str());
	if (!fs::exists(modName)) {
		printf("No mod exists with name '%s'\n", modName.c_str());
		return;
	}
	Project modProj(modName);
	nlohmann::json settings = Settings::ReadSettings();
	if (!Settings::HasSetting("gameDir")) {
		printf("Please setup the MDK before creating/updating a mod!\n");
		return;
	}
	std::string gameDir = settings["gameDir"];
	fs::path gamePath = gameDir;
	fs::path assetsPath = gamePath / "Assets";
	fs::path modVanillaPath = modProj.GetVanillaPath();
	if (!fs::exists(modVanillaPath)) {
		fs::create_directory(modVanillaPath);
	}
	for (const auto& vanillaAsset : fs::recursive_directory_iterator(assetsPath)) {
		fs::path modCopyPath = modVanillaPath / vanillaAsset.path().string().substr(assetsPath.string().length()+1);
		if (vanillaAsset.is_directory())
			continue;
		fs::create_directories(modCopyPath.parent_path());
		if (fs::exists(modCopyPath)) {
			fs::remove(modCopyPath);
		}
		fs::copy_file(vanillaAsset, modCopyPath);
	}
	fs::path jetPath = modVanillaPath / "BTD5.jet";
	if (fs::exists(jetPath)) {
		JetFile jetFile;
		jetFile.Open(jetPath);
		for (const auto& entryName : jetFile.GetEntries()) {
			std::vector<uint8_t> strBytes = jetFile.ReadEntry(entryName);
			std::string jsonStr = std::string(reinterpret_cast<char*>(strBytes.data()), strBytes.size());
			fs::path extractLoc = modVanillaPath / entryName.substr(sizeof("Assets"));
			//Its a directory, ignore
			if (!extractLoc.has_extension()) {
				continue;
			}
			if (!fs::exists(extractLoc.parent_path())) {
				fs::create_directories(extractLoc.parent_path());
			}
			File extractedFile;
			if (!extractedFile.OpenWrite(extractLoc)) {
				printf("Failed to extract '%s'", entryName.c_str());
				continue;
			}
			extractedFile.WriteStr(jsonStr);
			extractedFile.Close();
		}
		jetFile.Close();
		fs::remove(jetPath);
	}
	printf("Updated assets\n");
}