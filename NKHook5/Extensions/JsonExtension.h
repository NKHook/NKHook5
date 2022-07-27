#pragma once

#include "Extension.h"
#include <nlohmann/json.hpp>

namespace NKHook5 {
	namespace Extensions {
		class JsonExtension : public Extension {
		public:
			JsonExtension(std::string name, std::string target);
			virtual void UseData(void* content, size_t contentLen);
			virtual void UseJsonData(nlohmann::json content);
		};
	}
}