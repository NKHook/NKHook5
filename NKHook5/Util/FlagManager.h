#pragma once

#include "NewFramework.h"

namespace NKHook5::Util {
	class FlagManager {
		std::map<uint64_t, std::string> flags;
	public:
		static bool IsVanilla(uint64_t id);

		FlagManager();
		//Registers at a specific ID
		void Register(uint64_t numeric, const std::string& text);
		//Registers at the next available ID
		uint64_t Register(const std::string& text);
		//Slowly check if the id is available
		bool IsIDAvailable(uint64_t id);
		uint64_t GetFlag(const std::string& name);
		std::string GetName(uint64_t flag);
		const std::map<uint64_t, std::string>& GetAll();
	};
}
