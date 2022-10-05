#pragma once

#include "Feature.h"

namespace DevKit {
	namespace Features {
		class PackSprite : public Feature {
		public:
			PackSprite();
			virtual std::string ActivatorArgs() override;
			virtual int MaxArgs() override;
			virtual void Run(std::vector<std::string> args) override;
		};
	}
}