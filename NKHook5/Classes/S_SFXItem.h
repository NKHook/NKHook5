#pragma once

#include "../Util/NewFramework.h"

namespace NKHook5::Classes {
	struct S_SFXItem {
		char pad_0000[12];//0x0000
		nfw::string mName;//0x000C
		float mCooldown;   //0x0024
		double mPlayAt;	   //0x0028
		char pad_0030[8];  //0x0030
	};

	static_assert(sizeof(S_SFXItem) == 0x38);
}