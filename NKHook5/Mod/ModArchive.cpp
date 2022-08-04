#include "ModArchive.h"

#include <nlohmann/json.hpp>

using namespace NKHook5::Mod;
namespace fs = std::filesystem;

ModArchive::ModArchive() {}

ModArchive::ModArchive(fs::path path)
{
	if (!this->Open(path)) {
		printf("Failed to open mod: %s", path.string().c_str());
		return;
	}
}

bool ModArchive::Open(fs::path path) {
	try {
		this->pArchive = ZipFile::Open(path.string());
		std::string infoDat;
		if (!this->ReadEntry("modinfo.json", &infoDat)) {
			printf("Error opening mod");
			return false;
		}

		nlohmann::json infoJson = nlohmann::json::parse(infoDat);
		if (infoJson.contains("authors")) {
			if (infoJson["authors"].is_array()) {
				for (const auto& author : infoJson["authors"]) {
					if (!author.is_string()) {
						printf("'authors' must be a list of strings!");
						break;
					}
					this->info.authors.push_back(author);
				}
			}
			else {
				printf("'authors' MUST be an array!");
			}
		}
		if (infoJson.contains("description")) {
			if (infoJson["description"].is_string()) {
				this->info.description = infoJson["description"];
			}
			else {
				printf("'description' must be a string!");
			}
		}
		if (infoJson.contains("discord")) {
			if (infoJson["discord"].is_string()) {
				this->info.discord = infoJson["discord"];
			}
			else {
				printf("'discord' must be a string!");
			}
		}
		if (infoJson.contains("github")) {
			if (infoJson["github"].is_string()) {
				this->info.github = infoJson["github"];
			}
			else {
				printf("'github' must be a string!");
			}
		}
		if (infoJson.contains("name")) {
			if (infoJson["name"].is_string()) {
				this->info.name = infoJson["name"];
			}
			else {
				printf("'name' must be a string!");
			}
		}
		if (infoJson.contains("version")) {
			if (infoJson["version"].is_string()) {
				this->info.version = infoJson["version"];
			}
			else {
				printf("'version' must be a string!");
			}
		}
		if (infoJson.contains("website")) {
			if (infoJson["website"].is_string()) {
				this->info.website = infoJson["website"];
			}
			else {
				printf("'website' must be a string!");
			}
		}
	}
	catch (std::exception& ex) {
		printf("Error whilst opening mod: %s", ex.what());
	}
}

const ModInfo& ModArchive::GetInfo()
{
	return this->info;
}