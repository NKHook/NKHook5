#pragma once

#include "../Images/BitmapImage.h"
#include "InfoBase.h"

namespace Common {
	namespace Sprites {
		using namespace Common;
		using namespace Common::Sprites;
		using namespace Common::Sprites::Images;

		namespace Documents {
			class Cell : public InfoBase {
				size_t x, y, w, h, ax, ay, aw, ah;
				BitmapImage* fullImage;
				BitmapImage* image;

				void ExtractImage();
			public:
				Cell();
				Cell(std::string name,
					size_t x,
					size_t y,
					size_t w,
					size_t h,
					size_t ax,
					size_t ay,
					size_t aw,
					size_t ah);
				Cell(std::string name,
					size_t x,
					size_t y,
					size_t w,
					size_t h,
					size_t ax,
					size_t ay,
					size_t aw,
					size_t ah,
					BitmapImage* fullImage);
				BitmapImage* ExtractedImage();
			};
		}
	}
}