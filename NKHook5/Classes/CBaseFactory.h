#pragma once

#include "CBaseFileIO.h"
#include "SFactoryData.h"
#include "JSON_PropertyReader.h"

#include <boost/shared_ptr.hpp>
#include <json_spirit/json_spirit.h>

#include <string>

namespace NKHook5::Classes {
	template<typename InfoType, typename StructureType>
	class CBaseFactory
	{
	public:
		JSON_PropertyReader propertyReader{};
		class CGameSystemPointers* pGamePtrs = nullptr; //0x0020
		char pad_0024[4]{}; //0x0024
		CBaseFileIO* pFileIO = nullptr; //0x0028
		char pad_002C[4]{}; //0x002C
		boost::shared_ptr<SFactoryData<InfoType>> factoryData; //0x0030
		std::string definitionsDir; //0x0038

		virtual ~CBaseFactory() = default;
		virtual InfoType* GetInfo(std::string file) = 0;
		virtual InfoType* GetInfo(std::map<std::string, json_spirit::Value> json) = 0;
	}; //Size: 0x0054
}