#include "ExtensionStep.h"

#include <Extensions/ExtensionManager.h>
#include <Files/File.h>

using namespace Common;
using namespace Common::Extensions;
using namespace Common::Files;
using namespace Common::Mod;
using namespace DevKit;
using namespace DevKit::Packager;
using namespace DevKit::Proj;
namespace fs = std::filesystem;

ExtensionStep::ExtensionStep() : PackageStep("ExtensionStep")
{
}

bool ExtensionStep::Execute(Project& proj, ZipBase& arch)
{
	//Load all extensions
	ExtensionManager::AddAll();
	//Get those that are custom documents
	std::vector<Extension*> customDocs = ExtensionManager::GetCustomDocuments();
	//Load all of their data
	for (Extension* doc : customDocs) {
		//Get the path on disk
		const std::string& targetPath = doc->GetTarget();
		fs::path pathOnDisk = proj.GetModPath() / targetPath.substr(sizeof("Assets"));

		//Check if it exists
		if (fs::exists(pathOnDisk)) {
			//Use the extension data
			File docFile(pathOnDisk);
			std::vector<uint8_t> docData = docFile.ReadBytes();
			doc->UseData(docData.data(), docData.size());
		}
	}
	//Happy :)
	return true;
}
