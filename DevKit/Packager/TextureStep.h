#pragma once

#include "PackageStep.h"

namespace DevKit {
	namespace Packager {
		class TextureStep : public PackageStep {
		public:
			TextureStep();

			virtual bool Execute(Project& proj, ZipBase& arch) override;
		};
	}
}