#include "SaveData.h"

#include <Logging/Logger.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "../Util/FlagManager.h"

using namespace NKHook5::Mod;
using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
namespace fs = std::filesystem;

extern NKHook5::Util::FlagManager g_towerFlags;
static SaveData* instance;

SaveData::SaveData()
{
	for (const auto& towerFlag : g_towerFlags.GetAll()) {
		this->towerUnlocks[towerFlag.second] = false;
	}
}

SaveData* SaveData::GetInstance()
{
	if (!instance) {
		instance = new SaveData();
	}
	return instance;
}

bool SaveData::Load(fs::path saveFile)
{
	Print(LogLevel::INFO, "Loading custom save data...");
	if (!fs::exists(saveFile)) {
		Print(LogLevel::WARNING, "Save file '%s' does not exist!", saveFile.string().c_str());
		return false;
	}
	std::ifstream saveStream(saveFile);
	std::string str((std::istreambuf_iterator<char>(saveStream)), std::istreambuf_iterator<char>());
	saveStream.close();
	nlohmann::json saveData = nlohmann::json::parse(str);
	if (!saveData.is_object()) {
		Print(LogLevel::ERR, "Couldn't load save file: saveData is not an object!");
		return false;
	}
	nlohmann::json& towerUnlocks = saveData["towerUnlocks"];
	if (!towerUnlocks.is_array()) {
		Print(LogLevel::ERR, "Couldn't load save file: towerUnlocks is not an array!");
		return false;
	}
	for (const auto& unlock : towerUnlocks) {
		if (!unlock.is_object()) {
			Print(LogLevel::WARNING, "Failed to read a tower unlock: it was not an object");
			continue;
		}
		if (!unlock["towerName"].is_string()) {
			Print(LogLevel::WARNING, "Failed to read a tower unlock: the name is not a string!");
			continue;
		}
		if (!unlock["unlocked"].is_boolean()) {
			Print(LogLevel::WARNING, "Failed to read a tower unlock: the status is not a boolean!");
			continue;
		}
		std::string towerName = unlock["towerName"];
		bool unlocked = unlock["unlocked"];

		this->towerUnlocks[towerName] = unlocked;
	}
	Print(LogLevel::INFO, "Custom save data loaded successfully!");
	return true;
}

bool SaveData::Save(fs::path saveFile)
{
	Print(LogLevel::INFO, "Saving custom save data...");
	nlohmann::json saveData = nlohmann::json::object();

	saveData["towerUnlocks"] = nlohmann::json::array();
	for (const auto& [towerName, unlocked] : this->towerUnlocks) {
		nlohmann::json unlock = nlohmann::json::object();

		unlock["towerName"] = towerName;
		unlock["unlocked"] = unlocked;

		saveData["towerUnlocks"].push_back(unlock);
	}

	std::ofstream file(saveFile);
	file << saveData;
	file.close();

	Print(LogLevel::INFO, "Custom save data successfully saved!");
	return true;
}

bool SaveData::IsTowerUnlocked(std::string towerName)
{
	return this->towerUnlocks[towerName];
}

void SaveData::SetTowerUnlocked(std::string towerName, bool status)
{
	this->towerUnlocks[towerName] = status;
}
