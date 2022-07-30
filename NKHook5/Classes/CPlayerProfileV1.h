#pragma once

#define _ITERATOR_DEBUG_LEVEL 0
#include <ghstl/string>
#include <map>

namespace NKHook5 {
	namespace Classes {
		class CPlayerProfileV1
		{
		public:
			class CGameSystemPointers* pGamePtrs; //0x0000
			char pad_0004[4]; //0x0004
			int32_t profileVersion[3]; //0x0008
			int32_t gameVersion[3]; //0x0014
			char pad_0020[132]; //0x0020
			std::map<uint64_t, bool> towerUnlocks; //0x00A4
			std::map<uint64_t, bool> unlockedLevel4; //0x00AC
			char pad_00B4[176]; //0x00B4
			ghstl::string locale; //0x0164
			char pad_017C[180]; //0x017C
			ghstl::string saveFileName; //0x0230
			char pad_0248[712]; //0x0248
		}; //Size: 0x0510

		static_assert(sizeof(std::map<uint64_t, bool>) == 8);
		static_assert(sizeof(CPlayerProfileV1) == 0x510);
	}
}