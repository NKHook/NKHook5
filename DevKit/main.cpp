#include "Features/CreateMod.h"
#include "Features/Feature.h"
#include "Features/Setup.h"
#include "Settings.h"

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

static std::map<Feature*, CLI::Option*> features;

int main(int argc, const char* argv[]) {
	features.emplace(new Setup(), nullptr);
	features.emplace(new CreateMod(), nullptr);

	CLI::App app("NKHook5 DevKit (" STRING(NKHOOK_BUILD_VERSION) ")");
	for (const auto& [feature, option] : features) {
		features[feature] = app.add_option(feature->ActivatorArgs(), feature->GetVariable(), feature->HelpDesc());
	}
	CLI11_PARSE(app, argc, argv);

	for (const auto& [feature, option] : features) {
		if (option != nullptr) {
			if (option->reduced_results().size() > 0) {
				feature->Run(option->reduced_results());
			}
		}
	}
}