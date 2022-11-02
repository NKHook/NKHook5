#pragma once

#include "../../Util/NewFramework.h"
#include "CRenderableTextureObject.h"

namespace NKHook5 {
	namespace Classes {
		class CSprite : public CRenderableTextureObject {
		public:
			overload_new

		public:
			char pad_00C8[60]; //0x00C8
		};

		static_assert(sizeof(CSprite) == 0x104);
	}
}