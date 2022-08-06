#pragma once

#include <string>

namespace DevKit {
	namespace Features {
		class Feature {
			std::string name;
			std::string helpDesc;
		public:
			Feature(std::string name, std::string helpDesc);
			const std::string& GetName();
			virtual std::string ActivatorArgs();
			virtual std::string& HelpDesc();
			virtual void Run();
		};
	}
}