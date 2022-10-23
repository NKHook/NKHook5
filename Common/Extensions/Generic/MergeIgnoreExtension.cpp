#include "MergeIgnoreExtension.h"

#include "../../Logging/Logger.h"

using namespace Common;
using namespace Common::Extensions;
using namespace Common::Extensions::Generic;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util;

MergeIgnoreExtension::MergeIgnoreExtension() : JsonExtension("MergeIgnore", "Assets/MergeIgnore.json")
{
}

bool MergeIgnoreExtension::IsCustomDocument()
{
	return true;
}

void MergeIgnoreExtension::UseJsonData(nlohmann::json content)
{
	//We need to safely handle exceptions
	try {
		//If the content isnt an array
		if (!content.is_array()) {
			//we cannot use it
			Print("MergeIgnore.json MUST be an array!");
			return;
		}
		//Iterate the array
		for (nlohmann::json globJson : content) {
			//Check if the elements are strings
			if (!globJson.is_string()) {
				//If not, skip
				Print("MergeIgnore.json entries must be strings!");
				continue;
			}
			//Turn the json string into a std::string
			std::string globStr = globJson.get<std::string>();
			//Create a new ignore glob with it
			this->ignoreGlobs.emplace_back(globStr);
		}
	}
	catch (std::exception& ex) {
		Print("Error parsing MergeIgnore.json: %s", ex.what());
	}
}

const std::vector<Glob>& MergeIgnoreExtension::GetIgnores()
{
	return this->ignoreGlobs;
}
