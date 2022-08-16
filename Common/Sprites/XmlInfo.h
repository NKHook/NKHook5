#pragma once

#include "TexInfo.h"

namespace Common {
	namespace Sprites {
		class XmlInfo : public TexInfo {
			bool required;
		public:
			XmlInfo(std::string name, TexType type, bool required = true);
		};
	}
}