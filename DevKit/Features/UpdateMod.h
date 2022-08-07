#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		class UpdateMod : public Feature {
		public:
			UpdateMod();
			virtual std::string ActivatorArgs() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}