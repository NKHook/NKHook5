#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace NKHook5 {
	namespace Util {
		class FlagManager {
			std::vector<std::pair<uint64_t, std::string>> flags;
		public:
			FlagManager();
			//Registers at a specific ID
			void Register(uint64_t numeric, std::string text);
			//Registers at the next available ID
			uint64_t Register(std::string text);
			//Slowly check if the id is available
			bool IsIDAvailable(uint64_t id);
			uint64_t GetFlag(std::string name);
			std::string GetName(uint64_t flag);
			const std::vector<std::pair<uint64_t, std::string>>& GetAll();
		};
	}
}