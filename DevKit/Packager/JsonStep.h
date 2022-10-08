#pragma once

#include "PackageStep.h"

namespace DevKit {
	namespace Packager {
		enum class JsonPkgRule {
			REPLACE,
			MERGE,
			STRIP
		};

		class JsonStep : public PackageStep {
			JsonPkgRule rule;
		public:
			JsonStep(JsonPkgRule rule);

			virtual bool Execute(Project& proj, ZipBase& arch) override;
		};
	}
}