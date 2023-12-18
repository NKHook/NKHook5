#pragma once

#include "NewFramework.h"

namespace NKHook5::Util {
	class FlagManager {
		nfw::map<uint64_t, nfw::string> flags;
	public:
		static bool IsVanilla(uint64_t id);

		FlagManager();
		//Registers at a specific ID
		void Register(uint64_t numeric, const nfw::string& text);
		//Registers at the next available ID
		uint64_t Register(const nfw::string& text);
		//Slowly check if the id is available
		bool IsIDAvailable(uint64_t id);
		uint64_t GetFlag(const nfw::string& name);
		nfw::string GetName(uint64_t flag);
		const nfw::map<uint64_t, nfw::string>& GetAll();
	};
}
