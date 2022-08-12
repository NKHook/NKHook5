#pragma once

#include <string>

namespace Common {
	namespace Sprites {
		enum class FrameType {
			UNKNOWN,
			PNG,
			JPNG
		};

		class FrameInfo {
			std::string name;
			FrameType type;
			size_t texw;
			size_t texh;
		public:
			FrameInfo(std::string name, FrameType type, size_t texw, size_t texh);
		};
	}
}