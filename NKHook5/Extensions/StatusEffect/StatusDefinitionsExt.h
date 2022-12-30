#pragma once

#include <Extensions/JsonExtension.h>

#include <string>
#include <vector>

namespace NKHook5
{
	namespace Extensions
	{
		namespace StatusEffect
		{
			using namespace Common;
			using namespace Common::Extensions;

			struct StatusDefinition
			{
				std::string type;
				std::string spriteInfo;
				std::string texture;
			};

			class StatusDefinitionsExt : public JsonExtension
			{
				std::vector<StatusDefinition> definitions;
			public:
				StatusDefinitionsExt();
				virtual const std::vector<StatusDefinition>& GetDefinitions() const;
				virtual void UseJsonData(nlohmann::json content);
			};
		}
	}
}