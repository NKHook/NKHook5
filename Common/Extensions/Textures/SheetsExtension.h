#pragma once

#include "../JsonExtension.h"
#include <string>
#include <vector>

namespace Common {
	namespace Extensions {
		namespace Textures {
			class SheetsExtension : public JsonExtension {
				std::vector<std::string> customSpritesheets;
			public:
				SheetsExtension();
				virtual bool IsCustomDocument();
				virtual void UseJsonData(nlohmann::json content);
				virtual const std::vector<std::string>& GetSheetNames();
			};
		}
	}
}