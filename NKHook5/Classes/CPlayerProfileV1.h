#pragma once

#include "Macro.h"
#include "../../Util/NewFramework.h"
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
			char pad_0020[144]; //0x0020
			nfw::map<uint64_t, bool> towerUnlocks; //0x00B0
			nfw::map<uint64_t, bool> unlockedLevel4; //0x00B8
			char pad_00C0[180]; //0x00C0
			std::string locale; //0x0174
			char pad_018C[180]; //0x018C
			std::string saveFileName; //0x0240
			char pad_0258[712]; //0x0258
		}; //Size: 0x0520

		static_assert(sizeof(std::map<uint64_t, bool>) == 8);
		static_assert(sizeof(CPlayerProfileV1) == 0x520);
	}
}