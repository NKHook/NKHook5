#pragma once

#include "InfoBase.h"
#include <string>

namespace Common {
	namespace Sprites {
		namespace Documents {
			enum class TexType {
				NONE,
				PNG,
				JPNG
			};

			class SpriteInfo : public InfoBase {
				TexType type;
				bool required;
			public:
				SpriteInfo();
				SpriteInfo(std::string name, TexType type, bool required = true);

				TexType GetTexType();
				bool IsRequired();
			};
		}
	}
}