#include "AssetServer.h"

#include <Extensions/Generic/MergeIgnoreExtension.h>
#include <Extensions/ExtensionManager.h>
#include <Logging/Logger.h>
#include <Util/Json/MergedDocument.h>
#include <Util/Xml/ReflectedDocument.h>

#include <rapidxml.hpp>
#include <rapidxml_ext.hpp>
#include <rapidxml_print.hpp>

using namespace Common;
using namespace Common::Extensions;
using namespace Common::Extensions::Generic;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util::Json;
using namespace Common::Util::Xml;
using namespace NKHook5;
using namespace NKHook5::Assets;
namespace fs = std::filesystem;

static AssetServer* server = nullptr;

AssetServer* AssetServer::GetServer() {
	if (server == nullptr) {
		server = new AssetServer();
	}
	return server;
}

void AssetServer::AddSource(AssetSource* source) {
	this->sources.push_back(source);
}

bool AssetServer::Has(fs::path assetPath)
{
	bool has = false;
	for (AssetSource* source : this->sources) {
		if (source->Has(assetPath)) {
			has = true;
			break;
		}
	}
	return has;
}

std::shared_ptr<Asset> AssetServer::Serve(fs::path assetPath, std::vector<uint8_t> vanilla) {
	for (const auto& cached : this->cache) {
		if (cached != nullptr) {
			if (cached->GetFullPath() == assetPath) {
				return cached;
			}
		}
	}

	//This applies to all xml, regardless of the bin
	if (assetPath.filename().string().ends_with(".xml")) {
		auto toCache = this->ServeXML(assetPath, vanilla);
		this->cache.push_back(toCache);
		return toCache;
	}

	//Get the bin type
	AssetBin theBin = FromPath(assetPath);

	//JSON files are only found in the json bin
	if (theBin == AssetBin::JSON || assetPath.filename().string().ends_with(".json")) {
		auto toCache = this->ServeJSON(assetPath, vanilla);
		this->cache.push_back(toCache);
		return toCache;
	}

	//Textures need to be from their own bin like json
	if (theBin == AssetBin::TEXTURES) {
		auto toCache = this->ServeGeneric(assetPath, vanilla);
		this->cache.push_back(toCache);
		return toCache;
	}

	return nullptr;
}

std::shared_ptr<Asset> AssetServer::ServeGeneric(fs::path assetPath, std::vector<uint8_t> vanilla) {
	std::vector<std::shared_ptr<Asset>> finds;
	for (AssetSource* source : this->sources) {
		std::shared_ptr<Asset> find = source->Find(assetPath);
		if (find != nullptr) {
			finds.push_back(find);
		}
	}

	if (finds.empty()) {
		return nullptr;
	}
	return finds[0];
}

std::shared_ptr<Asset> AssetServer::ServeJSON(fs::path assetPath, std::vector<uint8_t> vanilla) {

	//Determines if we should not merge with vanilla, or override entirely
	bool ignoreMerge = false;
	//Get the merge ignore extension
	MergeIgnoreExtension* mergeIgnores = (MergeIgnoreExtension*)ExtensionManager::GetByName("MergeIgnore");
	const std::vector<Glob>& ignoreGlobs = mergeIgnores->GetIgnores();
	//Check if the asset path matches any
	for (const Glob& glob : ignoreGlobs) {
		if (glob.Match(assetPath.string())) {
			ignoreMerge = true;
		}
	}

	std::vector<std::shared_ptr<Asset>> finds;
	for (AssetSource* source : this->sources) {
		std::shared_ptr<Asset> find = source->Find(assetPath);
		if (find != nullptr) {
			finds.push_back(find);
		}
	}

	try {
		MergedDocument merged;
		if (!vanilla.empty() && !ignoreMerge) {
			std::string vanillaStr(vanilla.begin(), vanilla.end());
			nlohmann::ordered_json vanillaJson = nlohmann::ordered_json::parse(vanillaStr, nullptr, true, true);
			merged.Add(vanillaJson);
		}
		
		for (std::shared_ptr<Asset> find : finds) {
			const std::vector<uint8_t>& findData = find->GetData();
			std::string findStr(findData.begin(), findData.end());
			nlohmann::ordered_json findJson = nlohmann::ordered_json::parse(findStr, nullptr, true, true);
			if (ExtensionManager::GetByTarget(assetPath.string()).empty())
				merged.Add(findJson);
			else
				merged.Add(findJson, MergeMode::INSERTIVE);
		}

		nlohmann::ordered_json mergedJson = merged.GetMerged();
		std::string mergedStr = mergedJson.dump();
		std::shared_ptr<Asset> mergedAsset = std::make_shared<Asset>(assetPath, std::vector<uint8_t>(mergedStr.begin(), mergedStr.end()));
		return mergedAsset;
	}
	catch (std::exception& ex) {
		Print("Error whilst merging JSON documents: %s", ex.what());
	}
	return nullptr;
}

std::shared_ptr<Asset> AssetServer::ServeXML(fs::path assetPath, std::vector<uint8_t> vanilla)
{
	try {
		std::vector<std::shared_ptr<Asset>> overrides;
		for (AssetSource* source : this->sources) {
			std::shared_ptr<Asset> find = source->Find(assetPath);
			if (find != nullptr) {
				overrides.push_back(find);
			}
		}

		std::shared_ptr<Asset> baseXmlAsset = nullptr;
		if (!overrides.empty()) {
			if (overrides.size() > 1) {
				Print(LogLevel::WARNING, "Multiple AssetSources want to override an XML file, please use RXML for modded XML when applicable!");
			}

			baseXmlAsset = overrides.front();
		}

		std::string baseXmlStr;
		if (!vanilla.empty()) {
			baseXmlStr = std::string((char*)vanilla.data(), vanilla.size());
		}
		if (baseXmlAsset != nullptr) {
			const std::vector<uint8_t>& baseXmlData = baseXmlAsset->GetData();
			baseXmlStr = std::string((char*)baseXmlData.data(), baseXmlData.size());
		}

		fs::path reflectivePath = assetPath;
		reflectivePath.replace_extension("rxml");
		std::vector<std::shared_ptr<Asset>> reflections;
		for (AssetSource* source : this->sources) {
			std::shared_ptr<Asset> find = source->Find(reflectivePath);
			if (find != nullptr) {
				reflections.push_back(find);
			}
		}

		if (!baseXmlStr.empty()) {
			rapidxml::xml_document<>* victimXml = new rapidxml::xml_document<>();
			victimXml->parse<0>((char*)baseXmlStr.c_str());
			for (std::shared_ptr<Asset> reflect : reflections) {
				if (reflect != nullptr) {
					const std::vector<uint8_t>& reflectData = reflect->GetData();
					std::string reflectStr((char*)reflectData.data(), reflectData.size());
					ReflectedDocument reflectDocument(reflectStr);
					reflectDocument.Reflect(victimXml);
				}
			}

			std::string finalAssetData;
			rapidxml::internal::print_node(std::back_inserter(finalAssetData), victimXml, 0, 0);
			std::shared_ptr<Asset> finalAsset = std::make_shared<Asset>(
				assetPath, 
				std::vector<uint8_t>(
						finalAssetData.begin(),
						finalAssetData.end()
					)
				);
			return finalAsset;
		}
	}
	catch (std::exception& ex) {
		Print(LogLevel::ERR, "An error occoured whilst serving an XML file: %s", ex.what());
	}
	return nullptr;
}