#pragma once

#include "Extension.h"
#include <vector>

namespace Common::Extensions::ExtensionManager {

	static inline std::vector<Extension**> storages;

	template<typename extension_t>
	extension_t** GetStorage()
	{
		static extension_t* extension = nullptr;
		return &extension;
	}

	//Funcs to add extensions
	void AddAll();
	template<typename extension_t>
	void AddExtension()
	{
		auto** storage = GetStorage<extension_t>();
		storages.push_back(reinterpret_cast<Extension**>(storage));
		*storage = new extension_t();
	}

	//Functions to get extensions
	Extension* GetByName(const std::string& name);
	std::vector<Extension*> GetByTarget(const std::string& target);

	//Get by type
	template<typename extension_t>
	extension_t* Get()
	{
		return *GetStorage<extension_t>();
	}

	//Gets extensions that are custom documents
	std::vector<Extension*> GetCustomDocuments();
}