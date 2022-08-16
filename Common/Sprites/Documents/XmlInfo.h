#pragma once

#include "TexInfo.h"

namespace Common {
	namespace Sprites {
		namespace Documents {
			class XmlInfo : public TexInfo {
				bool required;
			public:
				XmlInfo(std::string name, TexType type, bool required = true);
			};
		}
	}
}