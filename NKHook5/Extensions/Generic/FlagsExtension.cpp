#include "FlagsExtension.h"

using namespace NKHook5::Extensions::Generic;

FlagsExtension::FlagsExtension(std::string target) : JsonExtension(target) {

}

bool FlagsExtension::IsCustomDocument()
{
	return true;
}

void FlagsExtension::UseJsonData(nlohmann::json data) {
	try {
		for (nlohmann::json& customFlag : data) {
			std::string flagText = customFlag["string"];
			uint64_t flagId = customFlag["flag"];

			this->registeredFlags.emplace_back(flagText, flagId);
			printf("Registered a custom flag!\n");
		}
	}
	catch (std::exception& ex) {
		printf("Error parsing FlagExtension: %s", ex.what());
		printf("Did you format your %s file properly?", this->GetTarget().c_str());
	}
}

const std::vector<FlagDef>& FlagsExtension::GetFlags()
{
	return this->registeredFlags;
}
