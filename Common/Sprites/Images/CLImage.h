#pragma once

#include "Image.h"
#include "../../Graphics/CLImg.h"
#include <vector>

namespace Common {
	namespace Sprites {
		namespace Images {
			class CLImage : public Image {
				cl_mem gpuImage;
				size_t width;
				size_t height;
			public:
				CLImage();
				CLImage(std::vector<uint32_t> bmpColors, size_t width, size_t height);
				CLImage(std::vector<std::vector<uint32_t>> bmpColors, size_t width, size_t height);
				CLImage(cl_mem gpuImage, size_t width, size_t height);

				virtual size_t GetWidth() override;
				virtual size_t GetHeight() override;
				virtual uint32_t At(size_t x, size_t y) override;
				virtual std::vector<uint32_t> ColorBytes() override;
			};
		}
	}
}