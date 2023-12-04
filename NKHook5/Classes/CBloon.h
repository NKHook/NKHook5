#pragma once

#include "Macro.h"
#include "../Util/NewFramework.h"

#include "CCompoundSprite.h"
#include "CStatusEffect.h"

namespace NKHook5 {
	namespace Classes {
		class CBloon : public CCompoundSprite {
			overload_allocators;

		public:
			void ApplyEffect(class CStatusEffect* effect, bool damageMoabs)
			{
				return ThisCall<void, CBloon*, class CStatusEffect*, const bool&>(Sigs::CBloon_ApplyEffect, this, effect, damageMoabs);
			}
		};
	}
}