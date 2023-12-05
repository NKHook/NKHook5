#include "ModArchive.h"

#include <Logging/Logger.h>

#include <nlohmann/json.hpp>

using namespace Common::Files;
using namespace Common::Mod;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

namespace fs = std::filesystem;

ModArchive::ModArchive() : ZipBase::ZipBase() {}

ModArchive::ModArchive(fs::path path) : ZipBase::ZipBase(path) {}

bool ModArchive::Open(fs::path path) {
	return this->OpenRead(path);
}

bool ModArchive::OpenRead(fs::path path) {
	try {
		ZipBase::Open(path);
		std::vector<uint8_t> infoBytes = this->ReadEntry("modinfo.json");
		std::string infoDat = std::string(reinterpret_cast<char*>(infoBytes.data()), infoBytes.size());

		nlohmann::json infoJson = nlohmann::json::parse(infoDat);
		this->info = ModInfo(infoJson);
		return true;
	}
	catch (std::exception& ex) {
		Print(LogLevel::ERR, "Error whilst opening mod: %s", ex.what());
	}
	return false;
}

bool ModArchive::OpenWrite(fs::path path) {
	try {
		ZipBase::Open(path);

		std::vector<uint8_t> infoBytes = this->ReadEntry("modinfo.json");
		std::string infoDat = std::string(reinterpret_cast<char*>(infoBytes.data()), infoBytes.size());
		if (infoDat.empty()) {
			this->info = ModInfo();
		}
		else {
			nlohmann::json infoJson = nlohmann::json::parse(infoDat);
			this->info = ModInfo(infoJson);
		}
		return true;
	}
	catch (std::exception& ex) {

	}
	return false;
}

const ModInfo& ModArchive::GetInfo() const
{
	return this->info;
}

void ModArchive::SetInfo(ModInfo newInfo) {
	std::string newInfoStr = newInfo.Serialize().dump();
	std::vector<uint8_t> newInfoBytes(newInfoStr.begin(), newInfoStr.end());
	this->WriteEntry("modinfo.json", newInfoBytes);
	this->info = newInfo;
}