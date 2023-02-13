#include "ModInfo.h"

#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Mod;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

ModInfo::ModInfo()
{
}

ModInfo::ModInfo(nlohmann::json toParse)
{
	this->Initialize(toParse);
}

void ModInfo::Initialize(nlohmann::json infoJson)
{
	if (infoJson.contains("authors")) {
		if (infoJson["authors"].is_array()) {
			for (const auto& author : infoJson["authors"]) {
				if (!author.is_string()) {
					Print(LogLevel::ERR, "'authors' must be a list of strings!");
					break;
				}
				this->authors.push_back(author);
			}
		}
		else {
			Print(LogLevel::ERR, "'authors' MUST be an array!");
		}
	}
	if (infoJson.contains("description")) {
		if (infoJson["description"].is_string()) {
			this->description = infoJson["description"];
		}
		else {
			Print(LogLevel::ERR, "'description' must be a string!");
		}
	}
	if (infoJson.contains("discord")) {
		if (infoJson["discord"].is_string()) {
			this->discord = infoJson["discord"];
		}
		else {
			Print(LogLevel::ERR, "'discord' must be a string!");
		}
	}
	if (infoJson.contains("github")) {
		if (infoJson["github"].is_string()) {
			this->github = infoJson["github"];
		}
		else {
			Print(LogLevel::ERR, "'github' must be a string!");
		}
	}
	if (infoJson.contains("name")) {
		if (infoJson["name"].is_string()) {
			this->name = infoJson["name"];
		}
		else {
			Print(LogLevel::ERR, "'name' must be a string!");
		}
	}
	if (infoJson.contains("version")) {
		if (infoJson["version"].is_string()) {
			this->version = infoJson["version"];
		}
		else {
			Print(LogLevel::ERR, "'version' must be a string!");
		}
	}
	if (infoJson.contains("website")) {
		if (infoJson["website"].is_string()) {
			this->website = infoJson["website"];
		}
		else {
			Print(LogLevel::ERR, "'website' must be a string!");
		}
	}
	if (infoJson.contains("load_order"))
	{
		if (infoJson["load_order"].is_string())
		{
			std::string orderStr = infoJson["load_order"];
			if (orderStr == "BASE")
			{
				this->loadOrder = LoadOrder::BASE;
			}
			if (orderStr == "FIRST")
			{
				this->loadOrder = LoadOrder::FIRST;
			}
			if (orderStr == "ANY")
			{
				this->loadOrder = LoadOrder::ANY;
			}
			if (orderStr == "LAST")
			{
				this->loadOrder = LoadOrder::LAST;
			}
		}
		else {
			Print(LogLevel::ERR, "'load_order' must be a string!");
		}
	}
	else {
		this->loadOrder = LoadOrder::ANY;
	}
	if (infoJson.contains("incompatibilities"))
	{
		if (infoJson["incompatibilities"].is_array())
		{
			try {
				for (const std::string& incompat : infoJson["incompatibilities"])
				{
					this->incompatibilites.push_back(incompat);
				}
			}
			catch (std::exception& ex)
			{
				Print(LogLevel::ERR, "Unknown error '%s' while parsing 'incompatibilities' field in modinfo!");
			}
		}
	}
}
nlohmann::json ModInfo::Serialize() {
	nlohmann::json result;
	if (this->authors.size() > 0) {
		result["authors"] = this->authors;
	}
	if (this->description.length() > 0) {
		result["description"] = this->description;
	}
	if (this->discord.length() > 0) {
		result["discord"] = this->discord;
	}
	if (this->github.length() > 0) {
		result["github"] = this->github;
	}
	if (this->name.length() > 0) {
		result["name"] = this->name;
	}
	if (this->version.length() > 0) {
		result["version"] = this->version;
	}
	if (this->website.length() > 0) {
		result["website"] = this->website;
	}
	return result;
}

const std::string& ModInfo::GetName() const
{
	return this->name;
}
const std::string& ModInfo::GetDescription() const
{
	return this->description;
}
const std::string& ModInfo::GetVersion() const
{
	return this->version;
}
const std::vector<std::string>& ModInfo::GetAuthors() const
{
	return this->authors;
}
const std::string& ModInfo::GetWebsite() const
{
	return this->website;
}
const std::string& ModInfo::GetDiscord() const
{
	return this->discord;
}
const std::string& ModInfo::GetGithub() const
{
	return this->github;
}

const std::optional<LoadOrder> ModInfo::GetLoadOrder() const
{
	return this->loadOrder;
}

const std::optional<std::vector<std::string>> ModInfo::GetIncompatibilites() const
{
	return this->incompatibilites;
}

void ModInfo::SetName(std::string value) {
	this->name = value;
}
void ModInfo::SetDescription(std::string value) {
	this->description = value;
}
void ModInfo::SetVersion(std::string value) {
	this->version = value;
}
void ModInfo::SetAuthors(std::vector<std::string> value) {
	this->authors = value;
}
void ModInfo::SetWebsite(std::string value) {
	this->website = value;
}
void ModInfo::SetDiscord(std::string value) {
	this->discord = value;
}
void ModInfo::SetGithub(std::string value) {
	this->github = value;
}

void ModInfo::SetLoadOrder(LoadOrder value)
{
	this->loadOrder = value;
}

void ModInfo::SetIncompatibilities(std::vector<std::string> value)
{
	this->incompatibilites = value;
}
