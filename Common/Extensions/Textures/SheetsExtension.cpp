#include "SheetsExtension.h"

using namespace Common::Extensions::Textures;

SheetsExtension::SheetsExtension() : JsonExtension("SheetsExtension", "Assets/Textures/sheets.json") {

}

bool SheetsExtension::IsCustomDocument()
{
	return true;
}

void SheetsExtension::UseJsonData(nlohmann::json data) {
	try {
		if (!data.is_array()) {
			printf("A sheets.json file is not an array type! All sheets lists MUST be arrays!");
			return;
		}
		for (nlohmann::json& customSheet : data) {
			if (!customSheet.is_string()) {
				printf("Failed to register a spritesheet because it was not a string!");
				continue;
			}
			std::string sheetName = customSheet.get<std::string>();
			this->customSpritesheets.push_back(sheetName);
			printf("Registered a custom spritesheet '%s'!\n", sheetName.c_str());
		}
	}
	catch (std::exception& ex) {
		printf("Error parsing SheetsExtension: %s", ex.what());
		printf("Is your file formatted properly?");
	}
}

const std::vector<std::string>& SheetsExtension::GetSheetNames()
{
	return this->customSpritesheets;
}
