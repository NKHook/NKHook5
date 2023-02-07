#include "Setup.h"
#include "../Settings.h"

#include <Logging/Logger.h>

#include <iostream>
#include <filesystem>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace DevKit;
using namespace DevKit::Features;
namespace fs = std::filesystem;

Setup::Setup() : Feature("setup", "Setup the NKHook5 MDK") {

}

std::string Setup::ActivatorArgs() {
	return "-s, --setup";
}

bool Setup::FlagOnly()
{
	return true;
}

#define SETUP_SETTING_CHECK(name, setting) printf("\t"name": %s\n", settings.contains(setting) ? settings[setting].dump().c_str() : "MISSING")
#define HAS_SETTING(setting) settings.contains(setting)

bool AskYN(std::string question) {
	char choice;
	do
	{
		printf("%s %s\n", question.c_str(), "(y/n)");
		std::cin >> choice;
	} while (!std::cin.fail() && choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N');
	return choice == 'y' || choice == 'Y';
}

std::string AskStr(std::string question) {
	std::string choice;
	do
	{
		printf("%s\n", question.c_str());
		std::getline(std::cin, choice);
	} while (!std::cin.fail() && choice.length() == 0);
	return choice;
}

void Setup::Run(std::vector<std::string> args) {
	nlohmann::json& settings = Settings::ReadSettings();

	Print(LogLevel::INFO, "Welcome to the NKHook5 MDK setup!");
	bool noSettings = false;
	if (!settings.is_null()) {
		Print(LogLevel::INFO, "Current settings:");
		SETUP_SETTING_CHECK("Game Directory", "gameDir");
		SETUP_SETTING_CHECK("Executable Name", "exeName");
		SETUP_SETTING_CHECK("DRM Variant", "drm");
	}
	else {
		Print(LogLevel::ERR, "No settings found");
		noSettings = true;
	}

	bool clearSettings = noSettings;
	if (!noSettings)
		clearSettings = AskYN("Would you like to clear all existing setings?");

	if (!HAS_SETTING("gameDir") || !HAS_SETTING("exeName") || clearSettings) {
		bool retry = true;
		do {
			std::string exeStrPath = AskStr("Please enter your BTD5 exe full path (Do not include quotes! >> \" <<)");
			fs::path exePath = fs::path(exeStrPath);
			if (fs::exists(exePath)) {
				settings["gameDir"] = exePath.parent_path().string();
				settings["exeName"] = exePath.filename().string();
				retry = false;
			}
			else {
				Print(LogLevel::ERR, "Couldn't find file '%s'", exeStrPath.c_str());
			}
		} while (retry);
	}
	if (!HAS_SETTING("drm") || clearSettings) {
		std::string exeName = settings["exeName"];
		if (exeName == "BTD5-Win.exe") {
			settings["drm"] = "STEAM";
		}
		else if (exeName == "BTD5-Kong.exe") {
			settings["drm"] = "KARTRIDGE";
		}
		else {
			settings["drm"] = "UNKNOWN";
		}
	}

	Settings::SaveSettings();
}