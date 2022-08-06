#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		class CreateMod : public Feature {
		public:
			CreateMod();
			virtual std::string ActivatorArgs() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}