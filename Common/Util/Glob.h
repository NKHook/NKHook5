#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace Common {
	namespace Util {
		class Glob {
			std::vector<std::string> globParts;
		public:
			Glob() = default;
			Glob(std::string globStr);
			virtual bool Match(std::string path) const;
		};
	}
}