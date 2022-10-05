#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		class Test : public Feature {
		public:
			Test();
			virtual std::string ActivatorArgs() override;
			virtual bool FlagOnly() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}