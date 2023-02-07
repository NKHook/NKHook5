#include "Project.h"

#include <Files/File.h>
#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace DevKit;
using namespace DevKit::Proj;
namespace fs = std::filesystem;

Project::Project()
{
}

Project::Project(fs::path path)
{
	if (this->Open(path)) {
		return;
	}

	if (!fs::exists(path)) {
		fs::create_directory(path);
	}

	this->modInfoPath = path / "modinfo.json";
	this->vanillaAssetsPath = path / "Vanilla";
	this->modAssetsPath = path / "Mod";

	if (!fs::exists(this->modInfoPath)) {
		ModInfo info;
		info.SetName(path.filename().string());
		info.SetDescription("A really cool mod made using the NKHook5 MDK");
		info.SetVersion("1.0.0");
		info.SetAuthors({
			"DisabledMallis",
			"EnabledMallis"
		});
		info.SetWebsite("https://nkhook.github.io/");
		info.SetDiscord("NO DISCORD LINK");
		info.SetGithub("https://github.com/NKHook/NKHook5");
		nlohmann::json serialized = info.Serialize();
		std::string jsonDump = serialized.dump(4);
		File infoFile(this->modInfoPath);
		infoFile.WriteStr(jsonDump);
		Print(LogLevel::INFO, "Saved mod info at '%s'", this->modInfoPath.string().c_str());
	}
}

bool Project::Open(fs::path path)
{
	this->modInfoPath = path / "modinfo.json";
	this->vanillaAssetsPath = path / "Vanilla";
	this->modAssetsPath = path / "Mod";

	if (!fs::exists(path)) {
		Print(LogLevel::ERR, "Failed to open project '%s' since it does not exist", path.string().c_str());
		return false;
	}
	fs::path modInfo(this->modInfoPath);
	if (!fs::exists(modInfo)) {
		Print(LogLevel::ERR, "Failed to open project '%s' as it doesn't have a modinfo.json file", path.string().c_str());
		return false;
	}
	File modInfoFile(modInfo);
	nlohmann::json modInfoJson = nlohmann::json::parse(modInfoFile.ReadStr());
	this->info = ModInfo(modInfoJson);
	/*if (!fs::exists(this->vanillaAssetsPath)) {
		printf("Vanilla assets missing for mod '%s', consider updating!\n", this->info.GetName().c_str());
	}*/
	if (!fs::exists(this->modAssetsPath)) {
		fs::create_directory(this->modAssetsPath);
	}
	return true;
}

fs::path DevKit::Proj::Project::GetModInfoPath()
{
	return this->modInfoPath;
}

fs::path DevKit::Proj::Project::GetVanillaPath()
{
	return this->vanillaAssetsPath;
}

fs::path DevKit::Proj::Project::GetModPath()
{
	return this->modAssetsPath;
}

const ModInfo& Project::GetInfo()
{
	return this->info;
}
