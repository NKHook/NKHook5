#pragma once

#include "PackageStep.h"

namespace DevKit {
	namespace Packager {
		enum class VanillaTarget {
			JSON,
			ALL
		};

		class VanillaStep : public PackageStep {
			bool checkMod;
			VanillaTarget target;
		public:
			VanillaStep(bool checkMod, VanillaTarget target);

			virtual bool Execute(Project& proj, ZipBase& arch) override;
		};
	}
}