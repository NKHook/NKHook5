#pragma once

#include "CRenderableTextureObject.h"

namespace NKHook5 {
	namespace Classes {
		class CSprite : public CRenderableTextureObject {
			char pad_00C8[60]; //0x00C8
		};

		static_assert(sizeof(CSprite) == 0x104);
	}
}