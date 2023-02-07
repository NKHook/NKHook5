#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		class RunMerge : public Feature {
		public:
			RunMerge();
			virtual std::string ActivatorArgs() override;
			virtual int MaxArgs() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}