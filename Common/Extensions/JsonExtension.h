#pragma once

#include "Extension.h"
#include <nlohmann/json.hpp>

namespace Common {
	namespace Extensions {
		class JsonExtension : public Extension {
		public:
			JsonExtension(std::string name, std::string target);
			//Implement the base Extension class UseData, overridden to call UseJsonData when it is appropriate
			virtual void UseData(void* content, size_t contentLen);
			//Function for when json data is parsed by UseData
			virtual void UseJsonData(nlohmann::json content);
		};
	}
}