#pragma once

#include "../Proj/Project.h"

#include <Files/ZipBase.h>

#include <string>

namespace DevKit {
	namespace Packager {
		using namespace Common;
		using namespace Common::Files;
		using namespace Common::Mod;
		using namespace DevKit::Proj;

		class PackageStep {
			std::string stepName;
		public:
			PackageStep(std::string stepName);

			virtual bool Execute(Project& proj, ZipBase& arch);
		};
	}
}