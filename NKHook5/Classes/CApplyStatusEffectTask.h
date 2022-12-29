#pragma once

#include "CBloonTargetingFilter.h"
#include "CWeaponTask.h"

namespace NKHook5
{
	namespace Classes
	{
		class CApplyStatusEffectTask : public CWeaponTask
		{
		public:
			char pad_0124[4]; //0x0124
			uint64_t effectId; //0x0128
			char pad_0130[64]; //0x0130
			CBloonTargetingFilter bloonTargetFilter; //0x0170
		}; //Size: 0x0198

		static_assert(sizeof(CApplyStatusEffectTask) == 0x198);
	}
}