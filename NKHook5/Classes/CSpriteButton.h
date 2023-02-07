#pragma once

#include "CBaseButton.h"
#include "CSprite.h"

#include "../../Util/NewFramework.h"

namespace NKHook5 {
	namespace Classes {
		class CSpriteButton : public CBaseButton, public CSprite {
		public:
			overload_new

		public:
			CSpriteButton() : CSprite(nullptr, false, Vec2F(0, 0), true) {

			}
		};

		static_assert(sizeof(CSpriteButton) == 0x1D4);
	}
}