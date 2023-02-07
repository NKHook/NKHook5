#include "Settings.h"

#include <Files/File.h>
#include <Logging/Logger.h>

#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace DevKit;
namespace fs = std::filesystem;

static nlohmann::json settings;

nlohmann::json& Settings::ReadSettings() {
	if (!settings.is_null()) {
		return settings;
	}
	try {
		File confFile = File(fs::path("mdkconf.json"));
		std::string confData = confFile.ReadStr();
		settings = nlohmann::json::parse(confData);
		return settings;
	}
	catch (std::exception& ex) {
#ifdef _DEBUG
		Print(LogLevel::ERR, "Error reading config: %s", ex.what());
#endif
	}
	return settings;
}

void Settings::SaveSettings() {
	try {
		File confFile = File(fs::path("mdkconf.json"));
		confFile.WriteStr(settings.dump(4));
		Print(LogLevel::INFO, "Settings saved!");
	}
	catch (std::exception& ex) {
#ifdef _DEBUG
		Print(LogLevel::ERR, "Error reading config: %s", ex.what());
#endif
	}
}

bool Settings::HasSetting(std::string setting)
{
	return settings.contains(setting);
}
