#include "JsonExtension.h"

using namespace NKHook5::Extensions;

JsonExtension::JsonExtension(std::string name, std::string target) : Extension(name, target)
{
}

void JsonExtension::UseData(void* content, size_t contentLen)
{
	std::string strContent = std::string((char*)content, contentLen);
	nlohmann::json jsonContent = nlohmann::json::parse(strContent);
	this->UseJsonData(jsonContent);
}

void JsonExtension::UseJsonData(nlohmann::json content)
{
}
