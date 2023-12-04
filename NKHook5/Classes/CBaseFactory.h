#pragma once

#include <boost/shared_ptr.hpp>
#include "CBaseFileIO.h"
#include "SFactoryData.h"
#include <string>

namespace NKHook5 {
	namespace Classes {
		template<typename InfoType, typename StructureType>
		class CBaseFactory
		{
		public:
			char pad_0000[28]; //0x0000
			class CGameSystemPointers* pGamePtrs; //0x0020
			char pad_0024[4]; //0x0024
			CBaseFileIO* pFileIO; //0x0028
			char pad_002C[4]; //0x002C
			boost::shared_ptr<SFactoryData<InfoType>> factoryData; //0x0030
			std::string definitionsDir; //0x0038

			virtual ~CBaseFactory() = default;
		}; //Size: 0x0054
	}
}