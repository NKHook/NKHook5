#pragma once

#include "TexInfo.h"

namespace Common {
	namespace Sprites {
		class XmlInfo : public TexInfo {
		public:
			XmlInfo(std::string name, TexType type);
		};
	}
}