#pragma once

#include "../Images/BitmapImage.h"
#include "Animation.h"
#include "Cell.h"
#include "SpriteInfo.h"

#include <string>
#include <vector>

namespace Common {
	namespace Sprites {
		namespace Documents {
			using namespace Common;
			using namespace Common::Sprites;
			using namespace Common::Sprites::Images;

			class XmlInfo : public SpriteInfo {
				std::vector<Animation> animations;
				std::vector<Cell> cells;
				BitmapImage* image;
			public:
				XmlInfo();
				XmlInfo(std::string name, TexType type, bool required = true);
				XmlInfo(std::string name, TexType type, std::vector<Animation> animations, std::vector<Cell> cells, bool required = true);
				XmlInfo(std::string name, TexType type, std::vector<Animation> animations, std::vector<Cell> cells, BitmapImage* image, bool required = true);
			};
		}
	}
}