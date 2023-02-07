#pragma once

#include "CBloon.h"
#include <vector>
#include <string>

namespace NKHook5
{
	namespace Classes
	{
		struct SBloonInfo
		{
			std::vector<std::string> children;
			char pad_000C[4]; //0x000C
			std::string SpriteFile; //0x0010
			uint32_t typeFlag; //0x0028
			int32_t RBE; //0x002C
			float Radius; //0x0030
			char pad_0034[8]; //0x0034
			float SpeedMultiplier; //0x003C
			char pad_0040[20]; //0x0040
			float InitialHealth; //0x0054
			CBloon* baseInstance; //0x0058
			char pad_005C[12]; //0x005C
		}; //Size: 0x0068
		static_assert(sizeof(SBloonInfo) == 0x68);
	}
}