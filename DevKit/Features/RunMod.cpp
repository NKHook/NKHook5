#include "RunMod.h"
#include "../Settings.h"

#include <Logging/Logger.h>

#include <filesystem>

#include <Windows.h>
#include <nlohmann/json.hpp>

using namespace DevKit::Features;
using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
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
		Print(LogLevel::INFO, "Please run 'devkit.exe --setup' before running a mod!");
		return;
	}
	if (settings["gameDir"].is_null()) {
		Print(LogLevel::ERR, "No gameDir set! Did you run 'devkit.exe --setup'?");
		return;
	}
	if (settings["exeName"].is_null()) {
		Print(LogLevel::ERR, "No exeName set! Did you run 'devkit.exe --setup'?");
		return;
	}
	fs::path gameDir = settings["gameDir"];
	fs::path modDir = fs::canonical(modName);
	std::string exeName = settings["exeName"];
	Print(LogLevel::INFO, "Launching '%s' with mod '%s'", exeName.c_str(), modName.c_str());
	SetCurrentDirectoryA(gameDir.string().c_str());
	std::string launchCmd = exeName + " --LaunchMod " + modDir.string();
	system(launchCmd.c_str());
	SetCurrentDirectoryA(cd.string().c_str());
	Print(LogLevel::INFO, "Game termination detected, exiting...");
}
