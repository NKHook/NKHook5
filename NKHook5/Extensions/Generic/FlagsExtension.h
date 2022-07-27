#pragma once

#include "../JsonExtension.h"
#include <vector>

namespace NKHook5 {
	namespace Extensions {
		namespace Generic {
			class FlagsExtension : public JsonExtension {
				std::vector<std::string> registeredFlags;
			public:
				FlagsExtension(std::string name, std::string target);
				virtual bool IsCustomDocument();
				virtual void UseJsonData(nlohmann::json content);
				virtual const std::vector<std::string>& GetFlags();
			};
		}
	}
}