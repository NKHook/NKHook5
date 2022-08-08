#include "Package.h"

#include <Files/File.h>
#include <Files/JetFile.h>
#include <Files/ZipBase.h>
#include <Logging/Logger.h>
#include <Util/Json/MergedDocument.h>

#include <iostream>
#include <algorithm>
#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Util;
using namespace Common::Util::Json;
using namespace DevKit;
using namespace DevKit::Features;
namespace fs = std::filesystem;

Package::Package() : Feature("package", "Packages a mod into a given mod format")
{
}

std::string Package::ActivatorArgs()
{
	return "-p, --package";
}

int Package::MaxArgs()
{
	return 3;
}

void Package::Run(std::vector<std::string> args)
{
	std::string modName = args[0];
	ModFmt modFmt = ModFmt::NONE;
	fs::path modDir = modName;

	if (args.size() > 1) {
		std::transform(args[1].begin(), args[1].end(), args[1].begin(), [](unsigned char c) { return std::tolower(c); });
		if (args[1] == "nkh") {
			modFmt = ModFmt::NKH;
		}
		else if (args[1] == "assetbundles") {
			modFmt = ModFmt::ASSETBUNDLES;
		}
		else if (args[1] == "jet") {
			modFmt = ModFmt::JET;
		}
		else if (args[1] == "unpacked") {
			modFmt = ModFmt::UNPACKED;
		}
		else {
			modFmt = ModFmt::NONE;
		}
	}
	if (modFmt == ModFmt::NONE) {
		printf("When packaging a mod, you must choose a format.\n");
		printf("The NKHook5 DevKit supports many formats for mods. Each have their own pros and cons.\n");
		printf("NOTE: Some formats require the vanilla assets to be packaged with them. To avoid copyright infringement, its wise to not distribute mods with these formats.\n");
		printf("\n");
		printf("1. nkh\n");
		printf("\tFormat made for mods that use NKHook5 and its features\n");
		printf("\tPros:\n");
		printf("\t- Small file size (easy to distribute)\n");
		printf("\t- No vanilla assets required\n");
		printf("\t- Can take full advantage of NKHook5's features\n");
		printf("\t- Allows your mod to work with other mods by default\n");
		printf("\tCons:\n");
		printf("\t- Requires NKHook5 to use\n");
		printf("\t- May be a little slower on older machines (due to extreme compression)\n");
		printf("2. AssetBundles\n");
		printf("\tA format made by Ninja Kiwi to allow them to update certain parts of their games to save on resources\n");
		printf("\tPros:\n");
		printf("\t- Does not require NKHook5\n");
		printf("\t- No vanilla assets required\n");
		printf("\t- Can allow your mod to work with other mods\n");
		printf("\tCons:\n");
		printf("\t- May not be able to make use of NKHook5's features\n");
		printf("\t- Proprietary\n");
		printf("3. jet\n");
		printf("\tA format made by Ninja Kiwi for protecting assets from being tampered (how naive)\n");
		printf("\tPros:\n");
		printf("\t- Most popular format for mods before AssetBundles was used\n");
		printf("\tCons:\n");
		printf("\t- Requires vanilla assets\n");
		printf("\t- Requires user to replace files to use\n");
		printf("\t- The devkit only packages JSON assets into the file\n");
		printf("4. Unpacked archive\n");
		printf("\tNot really a format for mod use, but can be used to share mod source code\n");
		printf("\tPros:\n");
		printf("\t- Git not required for mod collaboration\n");
		printf("\tCons:\n");
		printf("\t- Only one person can edit a file in the mod at a time to avoid conflict\n");
		printf("\t- Very hard to install as a mod\n");
		printf("\t- Large file size\n");
		printf("\t- Includes vanilla assets\n");
		int choice = 0;
#define CHECK_CHOICE(v) (v > 0 && v < 5)
		do {
			if (CHECK_CHOICE(choice))
				break;
			printf("\nWhich format would you like to use? (1-4): ");
			if (!(std::cin >> choice)) {
				printf("Error, please try again.");
				std::cin.clear();
				std::cin.ignore();
			}
		} while (true);
		modFmt = (ModFmt)choice;
	}

	if (modFmt == ModFmt::NONE) {
		printf("Please specify a valid mod format!\n");
		return;
	}

	if (modFmt == ModFmt::UNPACKED) {
		printf("Creating unpacked package...\n");
		ZipBase unpackedArch;
		if (!unpackedArch.Open(modName + "_sources.zip")) {
			printf("Failed to open archive to unpack\n");
			return;
		}
		size_t idx = -1;
		for (const auto& dirEntry : fs::recursive_directory_iterator(modDir)) {
			idx++;
			if (dirEntry.is_directory()) {
				continue;
			}
			fs::path entryPath = dirEntry.path();
			File entryFile;
			if (!entryFile.OpenRead(entryPath)) {
				printf("Failed to read file '%s'\n", entryPath.string().c_str());
				continue;
			}
			std::vector<uint8_t> dataBytes = entryFile.ReadBytes();
			if (dataBytes.empty()) {
				printf("File read was empty for '%s', skipping...\n", entryPath.string().c_str());
				continue;
			}
			entryFile.Close();
			if (!unpackedArch.WriteEntry(entryPath.string(), dataBytes)) {
				printf("Failed to save entry '%s'", entryPath.string().c_str());
				continue;
			}
			//Logger::Print("Packed file '%s'\n", entryPath.string().c_str());
			Logger::Progress(idx, 0, "Packaged files: ");
		}
		unpackedArch.Close();
		printf("Done!\n");
	}

	if (modFmt == ModFmt::JET) {
		Logger::Print("Creating jet package...");
		JetFile jetFile;
		if (!jetFile.Open(modName + ".jet")) {
			Logger::Print("Failed to create jet file");
			return;
		}
		fs::path modAssets = modDir / "Mod";
		fs::path vanillaAssets = modDir / "Vanilla";
		Logger::Print("Indexing mod files...");
		size_t numModFiles = 0;
		for (const auto& filePath : fs::recursive_directory_iterator(modAssets)) {
			if (filePath.is_directory()) {
				continue;
			}
			numModFiles++;
		}

		Logger::Print("Indexing vanilla files...");
		size_t numVanillaFiles = 0;
		for (const auto& filePath : fs::recursive_directory_iterator(vanillaAssets)) {
			if (filePath.is_directory()) {
				continue;
			}
			numVanillaFiles++;
		}

		Logger::Print("\n");

		size_t idx = 0;
		//Add all vanilla assets
		for (const auto& assetFile : fs::recursive_directory_iterator(vanillaAssets)) {
			if (assetFile.is_directory()) {
				continue;
			}
			idx++;
			fs::path onDisk = assetFile.path();
			fs::path modFile = modAssets / onDisk.string().substr(vanillaAssets.string().length()+1);
			fs::path entryPath = "Assets/" + onDisk.string().substr(vanillaAssets.string().length()+1);
			if (entryPath.string().find("Assets/JSON") == std::string::npos) {
				continue;
			}

			File theAsset;
			if (!theAsset.OpenRead(assetFile)) {
				Logger::Print("Failed to read file '%s'", entryPath.string().c_str());
				continue;
			}
			std::vector<uint8_t> dataBytes = theAsset.ReadBytes();
			if (dataBytes.empty()) {
				Logger::Print("File read was empty for '%s', skipping...", entryPath.string().c_str());
				continue;
			}
			theAsset.Close();
			if (!jetFile.WriteEntry(entryPath.string(), dataBytes)) {
				printf("Failed to save entry '%s'", entryPath.string().c_str());
				continue;
			}

			Logger::Progress(idx, numVanillaFiles, "Packaged vanilla assets: ");
		}

		Logger::Print("\n");

		idx = 0;
		//Add all mod assets and merge if needed
		for (const auto& assetFile : fs::recursive_directory_iterator(modAssets)) {
			if (assetFile.is_directory()) {
				continue;
			}
			idx++;
			fs::path onDisk = assetFile.path();
			fs::path vanillaFile = vanillaAssets / onDisk.string().substr(modAssets.string().length()+1);
			fs::path entryPath = "Assets/" + onDisk.string().substr(modAssets.string().length()+1);
			if (entryPath.string().find("Assets/JSON") == std::string::npos) {
				continue;
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
							nlohmann::ordered_json vanillaJson = nlohmann::ordered_json::parse(vanillaStr);
							nlohmann::ordered_json modJson = nlohmann::ordered_json::parse(modStr);

							MergedDocument merger;
							merger.Add(vanillaJson);
							merger.Add(modJson);
							nlohmann::ordered_json result = merger.GetMerged();

							std::string resultStr = result.dump();
							dataBytes = std::vector<uint8_t>(resultStr.begin(), resultStr.end());
						}
						catch (std::exception& ex) {
							Logger::Print("Failed to merge '%s' and '%s' asset: %s", onDisk.string().c_str(), vanillaFile.string().c_str(), ex.what());
						}
					}
				}
			}

			if (!jetFile.WriteEntry(entryPath.string(), dataBytes)) {
				printf("Failed to save entry '%s'", entryPath.string().c_str());
				continue;
			}

			Logger::Progress(idx, numModFiles, "Packaged mod assets: ");
		}

		jetFile.Close();
		Logger::Print("Done!");
	}
}