#pragma once

#include <vector>

namespace Common {
	namespace Sprites {
		namespace Images {
			class Image {
			public:
				Image();
				virtual size_t GetWidth();
				virtual size_t GetHeight();
				virtual uint32_t At(size_t x, size_t y);
				virtual std::vector<uint32_t> ColorBytes();
			};
		}
	}
}