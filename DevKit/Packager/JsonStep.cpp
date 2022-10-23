#include "JsonStep.h"

#include <Extensions/Generic/MergeIgnoreExtension.h>
#include <Extensions/ExtensionManager.h>
#include <Files/File.h>
#include <Logging/Logger.h>
#include <Util/Json/StrippedDocument.h>
#include <Util/Json/MergedDocument.h>

using namespace Common;
using namespace Common::Extensions;
using namespace Common::Extensions::Generic;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Mod;
using namespace Common::Util;
using namespace Common::Util::Json;
using namespace DevKit;
using namespace DevKit::Packager;
using namespace DevKit::Proj;

JsonStep::JsonStep(JsonPkgRule rule) : PackageStep("JSON")
{
	this->rule = rule;
}

bool JsonStep::Execute(Project& proj, ZipBase& arch)
{
	fs::path modAssets = proj.GetModPath() / "JSON";
	if (!fs::exists(modAssets)) {
		Print("No json files, skipping...");
		return true;
	}
	fs::path vanillaAssets = proj.GetVanillaPath() / "JSON";
	Logger::Print("Indexing mod files...");
	size_t numModFiles = 0;
	for (const auto& filePath : fs::recursive_directory_iterator(modAssets)) {
		if (filePath.is_directory()) {
			continue;
		}
		numModFiles++;
	}

	size_t idx = 0;
	//Add all mod assets and merge if needed
	for (const auto& assetFile : fs::recursive_directory_iterator(modAssets)) {
		if (assetFile.is_directory()) {
			continue;
		}
		idx++;
		fs::path onDisk = assetFile.path();
		fs::path vanillaFile = vanillaAssets / onDisk.string().substr(modAssets.string().length() + 1);
		fs::path entryPath = "Assets/JSON/" + onDisk.string().substr(modAssets.string().length() + 1);

		//Determines if we should not merge with vanilla, or override entirely
		bool ignoreMerge = false;
		//Get the merge ignore extension
		MergeIgnoreExtension* mergeIgnores = (MergeIgnoreExtension*)ExtensionManager::GetByName("MergeIgnore");
		if (mergeIgnores) {
			const std::vector<Glob>& ignoreGlobs = mergeIgnores->GetIgnores();
			//Check if the asset path matches any
			for (const Glob& glob : ignoreGlobs) {
				if (glob.Match(entryPath.string())) {
					ignoreMerge = true;
				}
			}
		}

		File theAsset;
		if (!theAsset.OpenRead(assetFile)) {
			Logger::Print("Failed to read file '%s'", entryPath.string().c_str());
			continue;
		}
		std::vector<uint8_t> dataBytes = theAsset.ReadBytes();
		if (dataBytes.empty()) {
			theAsset.Close();
			Logger::Print("File read was empty for '%s', skipping...", entryPath.string().c_str());
			continue;
		}
		theAsset.Close();

		if (this->rule != JsonPkgRule::REPLACE) {
			if (fs::exists(vanillaFile)) {
				File vanillaAsset;
				if (!vanillaAsset.Open(vanillaFile)) {
					Logger::Print("Failed to open '%s', skipping merge step", vanillaFile.string().c_str());
				}
				else {
					std::string modStr = std::string((char*)dataBytes.data(), dataBytes.size());
					std::string vanillaStr = vanillaAsset.ReadStr();
					if (vanillaStr.empty()) {
						Logger::Print("The content of '%s' was empty, skipping merge", vanillaFile.string().c_str());
					}
					else {
						try {
							nlohmann::ordered_json vanillaJson = nlohmann::ordered_json::parse(vanillaStr, nullptr, true, true);
							nlohmann::ordered_json modJson = nlohmann::ordered_json::parse(modStr, nullptr, true, true);

							nlohmann::ordered_json result;
							if (this->rule == JsonPkgRule::MERGE) {
								MergedDocument merger;
								if(!ignoreMerge)
									merger.Add(vanillaJson);
								merger.Add(modJson);
								result = merger.GetMerged();
							}
							else if (this->rule == JsonPkgRule::STRIP) {
								StrippedDocument stripper; //Hehehe
								if(!ignoreMerge)
									stripper.Add(vanillaJson);
								stripper.Add(modJson);
								result = stripper.GetStripped();
							}
							else {
								Print(LogLevel::ERR, "Unknown merge rule for file! This should have been unreachable!");
								return false;
							}

							std::string resultStr = result.dump();
							dataBytes = std::vector<uint8_t>(resultStr.begin(), resultStr.end());
						}
						catch (std::exception& ex) {
							Logger::Print("Failed to merge '%s' and '%s' asset: %s", onDisk.string().c_str(), vanillaFile.string().c_str(), ex.what());
						}
					}
				}
			}
		}

		if (!arch.WriteEntry(entryPath.string(), dataBytes)) {
			printf("Failed to save entry '%s'", entryPath.string().c_str());
			continue;
		}
	}
	Logger::Progress(idx, numModFiles, "Packaged mod assets: ");
	return true;
}
