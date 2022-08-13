#pragma once

#include "TexInfo.h"
#include <string>

namespace Common {
	namespace Sprites {
		class FrameInfo : public TexInfo {
			size_t texw;
			size_t texh;
		public:
			FrameInfo(std::string name, TexType type, size_t texw, size_t texh);
		};
	}
}