#include "VanillaStep.h"

#include <Files/File.h>
#include <Logging/Logger.h>
#include <Util/Json/StrippedDocument.h>
#include <Util/Json/MergedDocument.h>

#include <filesystem>
#include <string>

using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace DevKit;
using namespace DevKit::Packager;
namespace fs = std::filesystem;

VanillaStep::VanillaStep(bool checkMod, VanillaTarget target) : PackageStep("Vanilla") {
	this->checkMod = checkMod;
	this->target = target;
}

bool VanillaStep::Execute(Project& proj, ZipBase& arch) {
	fs::path modAssets = proj.GetModPath();
	fs::path vanillaAssets = proj.GetVanillaPath();
	if (this->target == VanillaTarget::JSON) {
		modAssets /= "JSON";
		vanillaAssets /= "JSON";
	}

	Print("Packing vanilla assets...");

	for (const auto& vanillaFile : fs::recursive_directory_iterator(vanillaAssets)) {
		if (vanillaFile.is_directory()) {
			continue;
		}
		fs::path onDisk = vanillaFile.path();
		fs::path modFile = modAssets / onDisk.string().substr(vanillaAssets.string().length() + 1);
		fs::path entryPath = "Assets/JSON/" + onDisk.string().substr(vanillaAssets.string().length() + 1);

		File theAsset;
		if (!theAsset.OpenRead(vanillaFile)) {
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

		if (this->checkMod) {
			if (fs::exists(modFile)) {
				continue;
			}
		}

		arch.WriteEntry(entryPath.string(), dataBytes);
	}

	return true;
}