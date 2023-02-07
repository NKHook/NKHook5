#include "JsonExtension.h"

#include <Logging/Logger.h>

using namespace Common::Extensions;
using namespace Common::Logging::Logger;

JsonExtension::JsonExtension(std::string name, std::string target) : Extension(name, target)
{
}

void JsonExtension::UseData(void* content, size_t contentLen)
{
	std::string strContent = std::string((char*)content, contentLen);
	try {
		nlohmann::json jsonContent = nlohmann::json::parse(strContent, nullptr, true, true);
		this->UseJsonData(jsonContent);
	}
	catch (std::exception& ex) {
		Print(LogLevel::ERR, "Failed to read a JsonExtension: %s", ex.what());
	}
}

void JsonExtension::UseJsonData(nlohmann::json content)
{
}
