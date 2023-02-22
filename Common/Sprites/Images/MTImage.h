#pragma once

#include "Image.h"

#include <vector>

namespace Common {
	namespace Sprites {
		namespace Images {
			class MTImage : public Image {
				std::vector<uint32_t> colors;
				size_t width;
				size_t height;
			public:
				MTImage();
				MTImage(const std::vector<uint32_t>& bmpColors, size_t width, size_t height);
				MTImage(const std::vector<std::vector<uint32_t>>& bmpColors, size_t width, size_t height);
				virtual ~MTImage();

				virtual size_t GetWidth() const override;
				virtual size_t GetHeight() const override;
				virtual uint32_t At(size_t x, size_t y) const override;
				virtual std::vector<uint32_t> ColorBytes() override;
				virtual MTImage CopyImage();
				virtual MTImage CopyImage(size_t width, size_t height);
				virtual MTImage CopyImage(size_t x, size_t y, size_t width, size_t height);
				virtual bool PasteImage(const MTImage& other, size_t x = 0, size_t y = 0, int32_t width = -1, int32_t height = -1);
				virtual bool PasteChannel(const MTImage& other, int channel);
			};
		}
	}
}