#include "StatusDefinitionsExt.h"

#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Extensions;
using namespace Common::Logging::Logger;
using namespace NKHook5;
using namespace NKHook5::Extensions;
using namespace NKHook5::Extensions::StatusEffect;

//Just needs to implements the flags extension for towers only
StatusDefinitionsExt::StatusDefinitionsExt() : JsonExtension("StatusDefinitions", "Assets/JSON/StatusDefinitions/*.status")
{
}

void StatusDefinitionsExt::UseJsonData(nlohmann::json content)
{
	if (content.empty())
	{
		Print(LogLevel::ERR, "%s", "Received empty json data for a StatusDefinition");
		return;
	}
	if (!content.contains("Type"))
	{
		Print(LogLevel::ERR, "%s", "Received a StatusDefinition without a 'Type' property!");
		return;
	}
	if (!content.contains("SpriteInfo"))
	{
		Print(LogLevel::ERR, "%s", "Received a StatusDefinition without a 'SpriteInfo' property!");
		return;
	}
	if (!content.contains("Texture"))
	{
		Print(LogLevel::ERR, "%s", "Received a StatusDefinition without a 'Texture' property!");
		return;
	}
	if (!content.contains("ExceptMOAB"))
	{
		Print(LogLevel::ERR, "%s", "Received a StatusDefinition without a 'ExceptMOAB' property!");
		return;
	}

	this->definitions.emplace_back(
		StatusDefinition(
			content["Type"].get<std::string>(),
			content["SpriteInfo"].get<std::string>(),
			content["Texture"].get<std::string>(),
			content["ExceptMOAB"].get<bool>()
		)
	);
}

const std::vector<StatusDefinition>& StatusDefinitionsExt::GetDefinitions() const
{
	return this->definitions;
}