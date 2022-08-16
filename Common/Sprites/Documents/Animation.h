#pragma once

#include "Cell.h"
#include "InfoBase.h"

#include <vector>

namespace Common {
	namespace Sprites {
		namespace Documents {
			class Animation : InfoBase {
				std::vector<Cell> animCells;
			public:
				Animation();
				Animation(std::string name);
				Animation(std::string name, std::vector<Cell> cells);
			};
		}
	}
}