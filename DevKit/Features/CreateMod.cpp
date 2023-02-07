#include "CreateMod.h"

#include "../FeatureMgr.h"
#include "../Proj/Project.h"

#include <Logging/Logger.h>

#include <filesystem>

using namespace DevKit;
using namespace DevKit::Features;
using namespace DevKit::Proj;
using namespace Common::Logging::Logger;
namespace fs = std::filesystem;

CreateMod::CreateMod() : Feature("create_mod", "Create a new mod with a given name") {

}

std::string CreateMod::ActivatorArgs()
{
	return "-c, --create-mod";
}

void CreateMod::Run(std::vector<std::string> args) {
	std::string modName = args[0];
	Print(LogLevel::INFO, "Creating mod '%s'...", modName.c_str());

	if (fs::exists(modName)) {
		Print(LogLevel::INFO, "Mod already exists!");
		return;
	}

	Project modProj(modName);

	if (!fs::exists(modProj.GetModPath())) {
		fs::create_directory(modProj.GetModPath());
	}

	if (!fs::exists(modProj.GetVanillaPath())) {
		Feature* modUpdate = FeatureMgr::FindByName("update_mod");
		modUpdate->Run(args);
	}

	Print(LogLevel::INFO, "Created mod!");
}