#pragma once

#include <vector>

namespace Common {
	namespace Sprites {
		namespace Images {
			class Image {
			public:
				Image();
				virtual size_t GetWidth() const;
				virtual size_t GetHeight() const;
				virtual uint32_t At(size_t x, size_t y) const;
				virtual std::vector<uint32_t> ColorBytes();
			};
		}
	}
}