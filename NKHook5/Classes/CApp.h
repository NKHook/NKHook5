#pragma once

#include "boost/shared_ptr"
#include "CAssetBag.h"
#include "CFont.h"
#include "CGameSystemPointers.h"
#include "IBasePointers.h"
#include <ghstl/string>

namespace NKHook5 {
	namespace Classes {
		class CApp {
		public:
			char pad_0000[4]; //0x0004
			IBasePointers basePointers; //0x0008
			char pad_0074[60]; //0x0074
			ghstl::string versionNumber; //0x00B0
			char pad_00C8[144]; //0x00C8
			boost::shared_ptr<CAssetBag> pAssetBag; //0x0158
			CGameSystemPointers* pCGameSystemPointers; //0x0160
			char pad_0164[4]; //0x0164
			boost::shared_ptr<CFont> pFont; //0x0168
			char pad_0170[24]; //0x0170
			float secondTimer; //0x0188
			int32_t millis; //0x018C
			char pad_0190[8]; //0x0190
			ghstl::string locale; //0x0198
			char pad_01B0[20]; //0x01B0

		public:
			virtual ~CApp() {};
		};
	}
}