#pragma once

#include "PackageStep.h"

namespace DevKit {
	namespace Packager {
		class ExtensionStep : public PackageStep {
		public:
			ExtensionStep();
			virtual bool Execute(Project& proj, ZipBase& arch);
		};
	}
}