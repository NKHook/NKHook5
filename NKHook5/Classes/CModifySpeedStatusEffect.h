#pragma once

#include "CStatusEffect.h"


namespace NKHook5::Classes
{
	class CModifySpeedStatusEffect : public CStatusEffect
	{
	public:
		int unk1 = 2; //0x0028
		float mSpeedScale = 1.0f; //0x002C
		int unk2 = 0; //0x0030

		CModifySpeedStatusEffect(float speedScale) : mSpeedScale(speedScale)
		{

		}
	}; //Size: 0x0034
	static_assert(sizeof(CModifySpeedStatusEffect) == 0x34);
}
