#pragma once

#include "Extension.h"
#include <vector>

namespace NKHook5 {
	namespace Extensions {
		namespace ExtensionManager {
			void AddAll();
			void AddExtension(Extension* toAdd);
			std::vector<Extension*> GetByTarget(std::string target);
			std::vector<Extension*> GetCustomDocuments();
		}
	}
}