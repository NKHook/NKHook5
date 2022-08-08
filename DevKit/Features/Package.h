#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		enum class ModFmt {
			NONE,
			NKH,
			ASSETBUNDLES,
			JET,
			UNPACKED
		};

		class Package : public Feature {
		public:
			Package();
			virtual std::string ActivatorArgs() override;
			virtual int MaxArgs() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}