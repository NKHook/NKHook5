#include "FeatureMgr.h"

#include <map>

#include <CLI/CLI.hpp>

using namespace DevKit;
using namespace DevKit::Features;

static std::map<Feature*, CLI::Option*> allFeatures;

Feature* FeatureMgr::RegisterFeature(Feature* registrant) {
	allFeatures.emplace(registrant, nullptr);
	return registrant;
}

std::map<Feature*, CLI::Option*>& FeatureMgr::AllFeatures()
{
	return allFeatures;
}

Feature* FeatureMgr::FindByName(std::string featureName)
{
	for (const auto& [f, opt] : allFeatures) {
		if (f->GetName() == featureName) {
			return f;
		}
	}
	return nullptr;
}
