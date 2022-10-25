#pragma once

#include "PackageStep.h"

namespace DevKit {
	namespace Packager {
		class LocStep : public PackageStep {
		public:
			LocStep();

			virtual bool Execute(Project& proj, ZipBase& arch) override;
		};
	}
}