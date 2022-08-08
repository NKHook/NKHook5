#include "ModArchive.h"

#include <nlohmann/json.hpp>

using namespace Common::Files;
using namespace Common::Mod;

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
		printf("Error whilst opening mod: %s", ex.what());
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

const ModInfo& const ModArchive::GetInfo() const
{
	return this->info;
}
