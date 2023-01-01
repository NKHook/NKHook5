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
			float duration; //0x0130
			float damageRate; //0x0134
			int32_t numPersists; //0x0138
			float initialTimer; //0x013C
			float speedScale; //0x0140
			float targetSpeed; //0x0144
			int32_t viralDepth; //0x0148
			float percentageChance; //0x014C
			char pad_0150[4]; //0x0150
			bool kill; //0x0154
			char pad_0155[3]; //0x0155
			int32_t fireMode; //0x0158
			int32_t applyDelay; //0x015C
			float bloonLifetime; //0x0160
			float rangeFromTower; //0x0164
			int32_t amount; //0x0168
			bool shredsMultipleLayers; //0x016C
			char pad_016D[3]; //0x016D
			CBloonTargetingFilter bloonTargetFilter; //0x0170
			bool ignoreImmunity; //0x018C
			char pad_018D[3]; //0x018D
		}; //Size: 0x0198

		static_assert(sizeof(CApplyStatusEffectTask) == 0x190);
		static_assert(offsetof(CApplyStatusEffectTask, effectId) == 0x128);
	}
}