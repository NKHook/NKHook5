#pragma once

#include <nlohmann/json.hpp>

namespace DevKit {
	namespace Settings {
		nlohmann::json ReadSettings();
		void SaveSettings();
		bool HasSetting(std::string setting);
	}
}