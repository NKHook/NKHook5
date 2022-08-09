#include "FlagsExtension.h"

using namespace Common::Extensions::Generic;

FlagsExtension::FlagsExtension(std::string name, std::string target) : JsonExtension(name, target) {

}

bool FlagsExtension::IsCustomDocument()
{
	return true;
}

void FlagsExtension::UseJsonData(nlohmann::json data) {
	try {
		if (!data.is_array()) {
			printf("A Flags.json file is not an array type! All flag lists MUST be arrays!\n");
			return;
		}
		for (nlohmann::json& customFlag : data) {
			if (!customFlag.is_string()) {
				printf("Failed to register a flag because it was not a string!\n");
				continue;
			}
			std::string flagStr = customFlag;
			this->registeredFlags.push_back(flagStr);
			printf("Registered a custom flag '%s'!\n", flagStr.c_str());
		}
	}
	catch (std::exception& ex) {
		printf("Error parsing FlagExtension: %s\n", ex.what());
		printf("Did you format your %s file properly?\n", this->GetTarget().c_str());
	}
}

const std::vector<std::string>& FlagsExtension::GetFlags()
{
	return this->registeredFlags;
}
