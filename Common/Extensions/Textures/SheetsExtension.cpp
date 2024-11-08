#include "SheetsExtension.h"

#include <Logging/Logger.h>

using namespace Common::Extensions::Textures;
using namespace Common::Logging::Logger;

SheetsExtension::SheetsExtension() : JsonExtension("SheetsExtension", "Assets/Textures/sheets.json") {

}

bool SheetsExtension::IsCustomDocument()
{
	return true;
}

void SheetsExtension::UseJsonData(nlohmann::json data) {
	try {
		if (!data.is_array()) {
			Print(LogLevel::ERR, "A sheets.json file is not an array type! All sheets lists MUST be arrays!");
			return;
		}
		for (nlohmann::json& customSheet : data) {
			if (!customSheet.is_string()) {
				Print(LogLevel::ERR, "Failed to register a spritesheet because it was not a string!");
				continue;
			}
			std::string sheetName = customSheet.get<std::string>();
			this->customSpritesheets.push_back(sheetName);
			Print(LogLevel::INFO, "Registered a custom spritesheet '%s'!", sheetName.c_str());
		}
	}
	catch (std::exception& ex) {
		Print(LogLevel::ERR, "Error parsing SheetsExtension: %s", ex.what());
		Print(LogLevel::ERR, "Is your file formatted properly?");
	}
}

const std::vector<std::string>& SheetsExtension::GetSheetNames()
{
	return this->customSpritesheets;
}
