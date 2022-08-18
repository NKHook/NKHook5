#pragma once

#include "Cell.h"
#include "InfoBase.h"

#include <vector>

#include <rapidxml.hpp>

namespace Common {
	namespace Sprites {
		namespace Documents {
			class Animation : InfoBase {
				std::vector<Cell*> animCells;
				BitmapImage* fullImage;
			public:
				Animation();
				Animation(std::string name);
				Animation(std::string name, std::vector<Cell*> cells);
				Animation(std::string name, std::vector<Cell*> cells, BitmapImage* fullImage);
			public:
				static Animation* FromNode(rapidxml::xml_node<>*, BitmapImage* fullImage);
			};
		}
	}
}