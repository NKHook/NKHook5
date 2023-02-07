#include "RunMerge.h"

#include <Logging/Logger.h>
#include <Util/Timer.h>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util;
using namespace DevKit;
using namespace DevKit::Features;

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
	Timer timer("PackSprite");
	if (args.size() == 0) {
		Print(LogLevel::ERR, "No sprite file given to %s", this->GetName());
	}
	std::string modName = args[0];
	std::string filePath = args[1];
}
