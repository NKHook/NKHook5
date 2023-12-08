#pragma once

#include <vector>
#include <string>

namespace NKHook5::Classes
{
	struct SBloonInfo {
		std::vector<std::string> mChildBloons;
		char pad_000C[4]; //0x000C
		nfw::string mSpriteFile; //0x0010
		uint32_t mStatusImmunity; //0x0028
		int32_t mRBE; //0x002C
		float mRadius; //0x0030
		char pad_0034[4]; //0x0034
		float N000025E0; //0x0038
		float mSpeedMultiplier; //0x003C
		bool mCanGoUnderground; //0x0040
		bool mRotateToPathDirection; //0x0041
		char pad_0042[18]; //0x0042
		float mInitialHealth; //0x0054
		char pad_0058[8]; //0x0058

	}; //Size: 0x0068
	static_assert(sizeof(SBloonInfo) == 0x60);
}