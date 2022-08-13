#include "Features/CreateMod.h"
#include "Features/Feature.h"
#include "Features/Package.h"
#include "Features/RunMod.h"
#include "Features/Setup.h"
#include "Features/SplitSprite.h"
#include "Features/UpdateMod.h"
#include "Settings.h"
#include "FeatureMgr.h"

#include <Util/Macro.h>
#include <Files/File.h>

#include <stdio.h>
#include <filesystem>
#include <map>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

using namespace Common;
using namespace Common::Files;
using namespace DevKit;
using namespace DevKit::Features;
namespace fs = std::filesystem;

int main(int argc, const char* argv[]) {
	std::cin.get();
	FeatureMgr::RegisterFeature(new Setup());
	FeatureMgr::RegisterFeature(new CreateMod());
	FeatureMgr::RegisterFeature(new UpdateMod());
	FeatureMgr::RegisterFeature(new RunMod());
	FeatureMgr::RegisterFeature(new Package());
	FeatureMgr::RegisterFeature(new SplitSprite());

	CLI::App app("NKHook5 DevKit (" STRING(NKHOOK_BUILD_VERSION) ")");
	for (const auto& [feature, option] : FeatureMgr::AllFeatures()) {
		if (feature->FlagOnly()) {
			FeatureMgr::AllFeatures()[feature] = app.add_flag(feature->ActivatorArgs(), feature->HelpDesc());
		}
		else {
			FeatureMgr::AllFeatures()[feature] = app.add_option(feature->ActivatorArgs(), feature->GetVariable(), feature->HelpDesc());
		}
		FeatureMgr::AllFeatures()[feature]->allow_extra_args(true);
		int maxArgs = feature->MaxArgs();
		FeatureMgr::AllFeatures()[feature]->expected(0, maxArgs);
	}
	CLI11_PARSE(app, argc, argv);

	for (const auto& [feature, option] : FeatureMgr::AllFeatures()) {
		if (option != nullptr) {
			if (option->reduced_results().size() > 0) {
				feature->Run(option->reduced_results());
			}
		}
	}
}