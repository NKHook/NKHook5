#include "ModArchive.h"

#include <nlohmann/json.hpp>

using namespace Common::Files;
using namespace Common::Mod;

namespace fs = std::filesystem;

ModArchive::ModArchive() : ZipBase::ZipBase() {}

ModArchive::ModArchive(fs::path path) : ZipBase::ZipBase(path) {}

bool ModArchive::Open(fs::path path) {
	try {
		ZipBase::Open(path);
		std::string infoDat;
		if (!this->ReadEntry("modinfo.json", &infoDat)) {
			printf("Error opening mod");
			return false;
		}

		nlohmann::json infoJson = nlohmann::json::parse(infoDat);
		this->info = ModInfo(infoJson);
	}
	catch (std::exception& ex) {
		printf("Error whilst opening mod: %s", ex.what());
	}
}

const ModInfo& const ModArchive::GetInfo() const
{
	return this->info;
}
