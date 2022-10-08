#include "PackageStep.h"

using namespace Common;
using namespace DevKit;
using namespace DevKit::Packager;
using namespace DevKit::Proj;

PackageStep::PackageStep(std::string stepName)
{
	this->stepName = stepName;
}

bool PackageStep::Execute(Project& proj, ZipBase& arch)
{
	return false;
}
