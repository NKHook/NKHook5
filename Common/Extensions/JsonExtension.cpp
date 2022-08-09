#include "JsonExtension.h"

using namespace Common::Extensions;

JsonExtension::JsonExtension(std::string name, std::string target) : Extension(name, target)
{
}

void JsonExtension::UseData(void* content, size_t contentLen)
{
	std::string strContent = std::string((char*)content, contentLen);
	try {
		nlohmann::json jsonContent = nlohmann::json::parse(strContent);
		this->UseJsonData(jsonContent);
	}
	catch (std::exception& ex) {
		printf("Failed to read a JsonExtension: %s\n", ex.what());
	}
}

void JsonExtension::UseJsonData(nlohmann::json content)
{
}
