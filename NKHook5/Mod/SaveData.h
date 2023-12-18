#pragma once

#include "../../Util/NewFramework.h"
#include <filesystem>
#include <string>
#include <map>

namespace NKHook5::Mod {
	class SaveData {
		nfw::map<nfw::string, bool> towerUnlocks;
		SaveData();
	public:
		static SaveData* GetInstance();
		bool Load(const std::filesystem::path& saveFile);
		bool Save(const std::filesystem::path& saveFile);

		bool IsTowerUnlocked(const nfw::string& towerName);
		void SetTowerUnlocked(const nfw::string& towerName, bool status);
	};
}