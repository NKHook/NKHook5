#pragma once

#include "Extension.h"
#include <vector>

namespace Common {
	namespace Extensions {
		namespace ExtensionManager {
			//Funcs to add extensions
			void AddAll();
			void AddExtension(Extension* toAdd);
			//Functions to get extensions
			Extension* GetByName(std::string name);
			std::vector<Extension*> GetByTarget(std::string target);
			//Get by type
			template<typename extension_t>
			extension_t* Get()
			{
				for (auto* extension : extensions)
				{
					auto* casted = dynamic_cast<extension_t*>(extension);
					if (casted != nullptr)
					{
						return casted;
					}
				}
				return nullptr;
			}
			//Gets extensions that are custom documents
			std::vector<Extension*> GetCustomDocuments();
		}
	}
}