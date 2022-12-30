#include "FlagsExtension.h"

using namespace Common::Extensions::Generic;

FlagsExtension::FlagsExtension(std::string name, std::string target) : JsonExtension(name, target) {

}

bool FlagsExtension::IsCustomDocument()
{
	return true;
}

//Flag injections should be defined in a json file as a list
void FlagsExtension::UseJsonData(nlohmann::json data) {
	try {
		//It must be a list/array
		if (!data.is_array()) {
			printf("A Flags.json file is not an array type! All flag lists MUST be arrays!\n");
			return;
		}
		//We want to iterate the list/array for each of the flag strings to register
		for (nlohmann::json& customFlag : data) {
			//We cannot register a flag type if it isn't a string
			if (!customFlag.is_string()) {
				printf("Failed to register a flag because it was not a string!\n");
				continue;
			}
			//Add the flag string to the registeredFlags list
			std::string flagStr = customFlag;
			this->registeredFlags.push_back(flagStr);
			printf("Registered a custom flag '%s'!\n", flagStr.c_str());
		}
	}
	//Error handling
	catch (std::exception& ex) {
		printf("Error parsing FlagExtension: %s\n", ex.what());
		printf("Did you format your %s file properly?\n", this->GetTarget().c_str());
	}

	this->UseFlagData(this->GetFlags());
}

//Gives the registered flags
const std::vector<std::string>& FlagsExtension::GetFlags()
{
	return this->registeredFlags;
}

void FlagsExtension::UseFlagData(const std::vector<std::string>& flags)
{

}