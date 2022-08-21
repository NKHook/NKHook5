#pragma once

#include "Image.h"
#include <stdint.h>
#include <vector>

namespace Common {
	namespace Sprites {
		namespace Images {
			class BitmapImage : public Image {
				std::vector<uint32_t> colorBytes;
				size_t width;
				size_t height;
			public:
				BitmapImage();
				BitmapImage(std::vector<uint32_t> bmpColors, size_t width, size_t height);
				BitmapImage(std::vector<std::vector<uint32_t>> bmpColors, size_t width, size_t height);

				virtual size_t GetWidth() override;
				virtual size_t GetHeight() override;
				virtual uint32_t At(size_t x, size_t y) override;
				virtual const std::vector<uint32_t>& ColorBytes() override;
			};
		}
	}
}