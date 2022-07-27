#pragma once

#include "../JsonExtension.h"
#include <vector>

namespace NKHook5 {
	namespace Extensions {
		namespace Generic {

			struct LocDef {
				std::string id;
				int l;
				std::string value;
			};

			class LocExtension : public JsonExtension {
				std::vector<LocDef> registeredLocs;
			public:
				LocExtension(std::string name, std::string target);
				virtual bool IsCustomDocument();
				virtual void UseJsonData(nlohmann::json content);
				virtual const std::vector<LocDef>& GetLocs();
			};
		}
	}
}