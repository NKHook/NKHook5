#include "LocStep.h"

#include <Files/File.h>
#include <Logging/Logger.h>

#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Mod;
using namespace DevKit;
using namespace DevKit::Packager;
using namespace DevKit::Proj;
namespace fs = std::filesystem;

LocStep::LocStep() : PackageStep("Loc")
{
}

bool LocStep::Execute(Project& proj, ZipBase& arch)
{
	try {
		fs::path locDir = proj.GetModPath() / "Loc";
		if (!fs::exists(locDir)) {
			Print("No locale to pack, skipping...");
			return true;
		}

		fs::path entryLoc = "Assets/Loc";
		for (const auto& file : fs::directory_iterator(locDir)) {
			fs::path filePath = file.path();
			fs::path entryPath = "Assets/Loc/" + filePath.string().substr(locDir.string().length() + 1);
			if (filePath.has_extension()) {
				if (filePath.extension() == ".xml") {
					Print(LogLevel::WARNING, "%s will override the XML file entirely. Consider using RXML to avoid merge issues with other mods!", filePath.string().c_str());
				}
			}

			File locFile;
			if (locFile.OpenRead(filePath)) {
				arch.WriteEntry(entryPath.string(), locFile.ReadBytes());
			}
			else {
				Print(LogLevel::ERR, "Failed to open %s (is it open in another program or deleted?)", filePath.string().c_str());
			}
		}
	}
	catch (std::exception& ex) {
		Print(LogLevel::ERR, "Error whilst packaging loc: %s", ex.what());
		return false;
	}

	return true;
}