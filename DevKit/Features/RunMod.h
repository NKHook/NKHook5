#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		class RunMod : public Feature {
		public:
			RunMod();
			virtual std::string ActivatorArgs() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}