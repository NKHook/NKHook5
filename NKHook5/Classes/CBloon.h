#pragma once

#include "Macro.h"
#include "../Util/NewFramework.h"

#include "CCompoundSprite.h"
#include "CStatusEffect.h"

namespace NKHook5::Classes {
	class CBloon : public CCompoundSprite {
		overload_allocators;

	public:
		void ApplyEffect(class CStatusEffect* effect, bool damageMoabs)
		{
			return ThisCall<Sigs::CBloon_ApplyEffect>(&CBloon::ApplyEffect, this, effect, damageMoabs);
		}
	};
}