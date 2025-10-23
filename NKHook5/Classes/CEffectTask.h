#pragma once

#include "CWeaponTask.h"
#include "eSFX_Items.h"

namespace NKHook5 {
	namespace Classes {
		class CEffectTask : public CWeaponTask {
		public:
			char pad_0124[48];//0x0124
			eSFX_Items mAudio = eSFX_Items::NONE;//0x0154
			uint16_t mAudioExt = 0;
		};
		static_assert(sizeof(CEffectTask) == 0x158);
		static_assert(offsetof(CEffectTask, mAudio) == 0x154);
	}// namespace Classes
}// namespace NKHook5