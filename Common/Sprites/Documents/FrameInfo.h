#pragma once

#include "Animation.h"
#include "Cell.h"
#include "SpriteInfo.h"
#include "InfoBase.h"

#include <filesystem>

namespace Common {
	namespace Sprites {
		namespace Documents {
			class FrameInfo : public SpriteInfo {
				size_t texW;
				size_t texH;
				std::vector<Animation*> animations;
				std::vector<Cell*> cells;
				BitmapImage* image;
			public:
				FrameInfo();
				FrameInfo(std::string name, TexType type, bool required = true);
				FrameInfo(std::string name, TexType type, size_t texW, size_t texH, bool required = true);
				FrameInfo(std::string name, TexType type, size_t texW, size_t texH, std::vector<Animation*> animations, std::vector<Cell*> cells, bool required = true);
				FrameInfo(std::string name, TexType type, size_t texW, size_t texH, std::vector<Animation*> animations, std::vector<Cell*> cells, BitmapImage* image, bool required = true);
			public:
				static FrameInfo* FromNode(std::filesystem::path docPath, rapidxml::xml_node<>*, std::string name, TexType type);
			};
		}
	}
}