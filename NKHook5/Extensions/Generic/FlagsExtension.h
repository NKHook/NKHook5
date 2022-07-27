#pragma once

#include "../JsonExtension.h"
#include <vector>

namespace NKHook5 {
	namespace Extensions {
		namespace Generic {
			struct FlagDef {
				std::string textId;
				uint64_t flagId;
			};

			class FlagsExtension : public JsonExtension {
				std::vector<FlagDef> registeredFlags;
			public:
				FlagsExtension(std::string name, std::string target);
				virtual bool IsCustomDocument();
				virtual void UseJsonData(nlohmann::json content);
				virtual const std::vector<FlagDef>& GetFlags();
			};
		}
	}
}