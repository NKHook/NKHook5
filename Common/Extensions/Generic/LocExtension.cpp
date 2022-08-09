#include "LocExtension.h"

using namespace Common::Extensions::Generic;

LocExtension::LocExtension(std::string name, std::string target) : JsonExtension(name, target) {

}

bool LocExtension::IsCustomDocument()
{
	return true;
}

void LocExtension::UseJsonData(nlohmann::json data) {
	try {
		if (!data.is_array()) {
			printf("A locale file is not an array type! All locale lists MUST be arrays!");
			return;
		}
		for (nlohmann::json& customLoc : data) {
			if (!customLoc.is_object()) {
				printf("Failed to register a locale key because it was not an object!");
				continue;
			}
			LocDef locDef;
			locDef.id = customLoc["id"];
			locDef.l = customLoc["l"];
			locDef.value = customLoc["value"];
			this->registeredLocs.push_back(locDef);
			printf("Registered a custom locale key '%s'!\n", locDef.id.c_str());
		}
	}
	catch (std::exception& ex) {
		printf("Error parsing FlagExtension: %s", ex.what());
		printf("Did you format your %s file properly?", this->GetTarget().c_str());
	}
}

const std::vector<LocDef>& LocExtension::GetLocs()
{
	return this->registeredLocs;
}
