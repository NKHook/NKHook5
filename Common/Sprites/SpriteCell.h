#pragma once

#include <string>

namespace Common {
	namespace Sprites {
		class SpriteCell {
		public:
			size_t x = 0;
			size_t y = 0;
			size_t w = 0;
			size_t h = 0;
			size_t ax = 0;
			size_t ay = 0;
			size_t aw = 0;
			size_t ah = 0;
			std::string name = "";
		public:
			SpriteCell(std::string name, size_t x, size_t y, size_t w, size_t h, size_t ax, size_t ay, size_t aw, size_t ah);
		};
	}
}