#pragma once

#include "../Images/BitmapImage.h"
#include "InfoBase.h"

#include <rapidxml.hpp>

namespace Common {
	namespace Sprites {
		using namespace Common;
		using namespace Common::Sprites;
		using namespace Common::Sprites::Images;

		namespace Documents {
			class Cell : public InfoBase {
				/* These are positioning values for how the game should align the images and such */
				size_t x; // X pos
				size_t y; // Y pos
				size_t w; // width
				size_t h; // height
				size_t ax; // origin-aligned X
				size_t ay; // origin-aligned Y
				size_t aw; // origin-aligned width
				size_t ah; // origin-aligned height
				/* 
				* Origin alignment effectively means how it should be placed if it was to
				* be rendered at the position (0,0)
				*/

				/* Pointers to NKH images so we can manipulate the cell image */
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
			public:
				static Cell* FromNode(rapidxml::xml_node<>* cellNode, BitmapImage* fullImage);
			};
		}
	}
}