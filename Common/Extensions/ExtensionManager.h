#pragma once

#include "Extension.h"
#include <vector>

namespace Common {
	namespace Extensions {
		namespace ExtensionManager {
			void AddAll();
			void AddExtension(Extension* toAdd);
			Extension* GetByName(std::string name);
			std::vector<Extension*> GetByTarget(std::string target);
			std::vector<Extension*> GetCustomDocuments();
		}
	}
}