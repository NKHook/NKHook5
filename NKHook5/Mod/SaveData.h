#pragma once

#include <filesystem>
#include <string>
#include <map>

namespace NKHook5 {
	namespace Mod {
		class SaveData {
			std::map<std::string, bool> towerUnlocks;
			SaveData();
		public:
			static SaveData* GetInstance();
			bool Load(std::filesystem::path saveFile);
			bool Save(std::filesystem::path saveFile);

			bool IsTowerUnlocked(std::string towerName);
			void SetTowerUnlocked(std::string towerName, bool status);
		};
	}
}