#pragma once

#include "CStatusEffect.h"

namespace NKHook5
{
	namespace Classes
	{
		class CModifySpeedStatusEffect : public CStatusEffect
		{
		public:
			char pad_0028[4]; //0x0028
			float mSpeedScale; //0x002C
			char pad_0030[4]; //0x0030
		}; //Size: 0x0034
		static_assert(sizeof(CModifySpeedStatusEffect) == 0x34);
	}
}