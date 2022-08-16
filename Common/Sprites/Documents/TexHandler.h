#pragma once

#include "SheetInfo.h"

namespace Common {
	namespace Sprites {
		namespace Documents {
			class TexHandler {
				std::shared_ptr<SheetInfo> extraSpriteInfo;
				std::shared_ptr<SheetInfo> fullSpriteInfo;
				std::shared_ptr<SheetInfo> spriteInfo;

				TexHandler();
			public:
				static TexHandler* GetInstance();
			};
		}
	}
}