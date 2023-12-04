#pragma once

#include "CAssetBag.h"
#include "CFont.h"
#include "CGameSystemPointers.h"
#include "IBasePointers.h"

#include <ghstl/string>
#include <boost/shared_ptr.hpp>

namespace NKHook5 {
	namespace Classes {
		class CApp {
		public:
			char pad_0000[4]; //0x0004
			IBasePointers basePointers; //0x0008
			char pad_0074[60]; //0x0074
			ghstl::string versionNumber; //0x00B0
			char pad_00C8[52]; //0x00C8
			int32_t hasBundles; //0x00FC
			char pad_0100[68]; //0x0100
			boost::shared_ptr<CAssetBag> pAssetBag; //0x0144
			CGameSystemPointers* pCGameSystemPointers; //0x014C
			char pad_0150[4]; //0x0150
			boost::shared_ptr<CFont> pFont; //0x0154
			char pad_015C[24]; //0x015C
			float secondTimer; //0x0174
			int32_t millis; //0x0178
			char pad_017C[8]; //0x017C
			ghstl::string locale; //0x0184
			char pad_019C[20]; //0x019C

		public:
			virtual ~CApp() {};
		};
	}
}