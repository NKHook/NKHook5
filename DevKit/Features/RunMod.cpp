#include "RunMod.h"
#include "../Settings.h"

#include <Windows.h>
#include <nlohmann/json.hpp>

#include <filesystem>

using namespace DevKit::Features;
namespace fs = std::filesystem;

RunMod::RunMod() : Feature("run_mod", "Runs BTD5 with a given mod")
{

}

std::string RunMod::ActivatorArgs()
{
	return "-r, --run, --run-mod";
}

void RunMod::Run(std::vector<std::string> args)
{
	std::string modName = args[0];
	fs::path cd = fs::current_path();
	nlohmann::json settings = Settings::ReadSettings();
	if (settings.is_null()) {
		printf("Please run 'devkit.exe --setup' before running a mod!\n");
		return;
	}
	if (settings["gameDir"].is_null()) {
		printf("No gameDir set! Did you run 'devkit.exe --setup'?\n");
		return;
	}
	if (settings["exeName"].is_null()) {
		printf("No exeName set! Did you run 'devkit.exe --setup'?\n");
		return;
	}
	fs::path gameDir = settings["gameDir"];
	fs::path modDir = fs::canonical(modName);
	std::string exeName = settings["exeName"];
	printf("Launching '%s' with mod '%s'\n", exeName.c_str(), modName.c_str());
	SetCurrentDirectoryA(gameDir.string().c_str());
	std::string launchCmd = exeName + " --LaunchMod " + modDir.string();
	system(launchCmd.c_str());
	SetCurrentDirectoryA(cd.string().c_str());
	printf("Game termination detected, exiting...\n");
}
