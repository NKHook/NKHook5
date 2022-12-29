#pragma once

#include "Macro.h"
#include "../Util/NewFramework.h"

#include "CStatusEffect.h"

namespace NKHook5 {
	namespace Classes {
		class CBloon {
			overload_new;

		public:
			void ApplyEffect(class CStatusEffect* effect, void* param_2)
			{
				return ThisCall<void, CBloon*, class CStatusEffect*, void*>(Sigs::CBloon_ApplyEffect, this, effect, param_2);
			}
		};
	}
}