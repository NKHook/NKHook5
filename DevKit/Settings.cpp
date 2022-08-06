#include "Settings.h"

#include <Files/File.h>

#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace DevKit;
namespace fs = std::filesystem;

static nlohmann::json settings;

nlohmann::json Settings::ReadSettings() {
	try {
		File confFile = File(fs::path("mdkconf.json"));
		std::string confData = confFile.ReadStr();
		settings = nlohmann::json::parse(confData);
		return settings;
	}
	catch (std::exception& ex) {
#ifdef _DEBUG
		printf("Error reading config: %s\n", ex.what());
#endif
	}
	return nlohmann::json::object();
}

void Settings::SaveSettings() {
	try {
		File confFile = File(fs::path("mdkconf.json"));
		confFile.WriteStr(settings.dump(4));
		printf("Settings saved!");
	}
	catch (std::exception& ex) {
#ifdef _DEBUG
		printf("Error reading config: %s\n", ex.what());
#endif
	}
}

bool Settings::HasSetting(std::string setting)
{
	return settings.contains(setting);
}
