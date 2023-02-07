#include "RunMerge.h"

#include "../Proj/Project.h"

#include <Files/File.h>
#include <Logging/Logger.h>
#include <Util/Timer.h>
#include <Util/Json/MergedDocument.h>
#include <Util/Json/StrippedDocument.h>

#include <nlohmann/json.hpp>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util;
using namespace Common::Util::Json;
using namespace DevKit;
using namespace DevKit::Features;
using namespace DevKit::Proj;

namespace fs = std::filesystem;

RunMerge::RunMerge() : Feature("run_merge", "Test to see how your JSON file will be merged")
{

}

std::string RunMerge::ActivatorArgs()
{
	return "-r, --rm, --runmerge";
}

int RunMerge::MaxArgs()
{
	return 2;
}

void RunMerge::Run(std::vector<std::string> args)
{
	Timer timer("RunMerge");
	if (args.size() == 0) {
		Print(LogLevel::ERR, "No mod name or file path given to %s", this->GetName());
		return;
	}
	if (args.size() == 1) {
		Print(LogLevel::ERR, "No file path given to %s", this->GetName());
		return;
	}
	std::string modName = args[0];
	std::string relFilePath = args[1];

	Project modProj;
	modProj.Open(modName);

	fs::path modPath = modProj.GetModPath();
	fs::path vanillaPath = modProj.GetVanillaPath();
	fs::path modFilePath = modPath / relFilePath;
	fs::path vanillaFilePath = vanillaPath / relFilePath;

	File modFile;
	if (!modFile.OpenRead(modFilePath))
	{
		Print(LogLevel::ERR, "Could not open file \"%s\"", modFilePath.string().c_str());
		return;
	}

	File vanillaFile;
	if (!vanillaFile.OpenRead(vanillaFilePath))
	{
		Print(LogLevel::ERR, "Cound not open file \"%s\"", vanillaFilePath.string().c_str());
		return;
	}

	try {
		std::string modContents = modFile.ReadStr();
		nlohmann::ordered_json modJson = nlohmann::ordered_json::parse(modContents);
		std::string vanillaContents = vanillaFile.ReadStr();
		nlohmann::ordered_json vanillaJson = nlohmann::ordered_json::parse(vanillaContents);

		Print(LogLevel::SUCCESS, "UN-MODIFIED FILE");
		Print("%s", modContents.c_str());
		Print(LogLevel::SUCCESS, "END OF FILE");

		Print(LogLevel::SUCCESS, "STRIPPED FILE");
		StrippedDocument stripper;
		stripper.Add(vanillaJson);
		stripper.Add(modJson);
		nlohmann::ordered_json strippedFile = stripper.GetStripped();
		std::string strippedStr = strippedFile.dump(4);
		Print("%s", strippedStr.c_str());
		Print(LogLevel::SUCCESS, "END OF FILE");

		Print(LogLevel::SUCCESS, "FINAL MERGE");
		MergedDocument merger;
		merger.Add(vanillaJson);
		merger.Add(strippedFile);
		nlohmann::ordered_json mergedFile = merger.GetMerged();
		std::string mergedStr = mergedFile.dump(4);
		Print("%s", mergedStr.c_str());
		Print(LogLevel::SUCCESS, "END OF FILE");
	}
	catch (std::exception& ex)
	{
		Print(LogLevel::ERR, "%s", ex.what());
	}
}
