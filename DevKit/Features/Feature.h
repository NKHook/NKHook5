#pragma once

#include <string>
#include <vector>

namespace DevKit {
	namespace Features {
		class Feature {
			std::string name;
			std::string helpDesc;
			std::string variable;
		public:
			Feature(std::string name, std::string helpDesc);
			const std::string& GetName();
			virtual std::string ActivatorArgs();
			virtual std::string& HelpDesc();
			virtual std::string& GetVariable();
			virtual bool FlagOnly();
			virtual int MaxArgs();
			virtual void Run(std::vector<std::string> args);
		};
	}
}