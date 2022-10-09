#pragma once

#include "Cell.h"
#include "InfoBase.h"

#include <vector>

#include <rapidxml.hpp>

namespace Common {
	namespace Sprites {
		namespace Documents {
			class Animation : public InfoBase {
				std::vector<Cell*> animCells;
			public:
				Animation();
				Animation(std::string name);
				Animation(std::string name, std::vector<Cell*> cells);
			public:
				static Animation* FromNode(rapidxml::xml_node<>*);
				static Animation* Create(
					std::string name,
					std::vector<Cell*> cells
				);

				const std::vector<Cell*>& GetCells();

				rapidxml::xml_node<>* ToXML(rapidxml::xml_document<>* document);
			};
		}
	}
}