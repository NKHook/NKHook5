#pragma once

#include "Image.h"

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.h>

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
				CLImage(const std::vector<uint32_t>& bmpColors, size_t width, size_t height);
				CLImage(const std::vector<std::vector<uint32_t>>& bmpColors, size_t width, size_t height);
				CLImage(cl_mem gpuImage, size_t width, size_t height);
				virtual ~CLImage();

				virtual size_t GetWidth() const override;
				virtual size_t GetHeight() const override;
				virtual uint32_t At(size_t x, size_t y) const override;
				virtual std::vector<uint32_t> ColorBytes() override;
				virtual CLImage* CopyImage();
				virtual CLImage* CopyImage(size_t width, size_t height);
				virtual CLImage* CopyImage(size_t x, size_t y, size_t width, size_t height);
				virtual bool PasteImage(CLImage* other, size_t x = 0, size_t y = 0, int32_t width = -1, int32_t height = -1);
				virtual bool PasteChannel(CLImage* other, int channel);
			};
		}
	}
}