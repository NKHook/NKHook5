#pragma once

#include "CTexture.h"

namespace NKHook5 {
	namespace Classes {
		struct SSpriteInfo {
			char pad_0000[4]; //0x0000
			CTexture* texture; //0x0004
		};
	}
}