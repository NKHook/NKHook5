#pragma once

#include "Features/Feature.h"

#include <string>

#include <CLI/CLI.hpp>

namespace DevKit {
	namespace FeatureMgr {
		using namespace Features;

		Feature* RegisterFeature(Feature*);
		std::map<Feature*, CLI::Option*>& AllFeatures();
		Feature* FindByName(std::string featureName);
	}
}