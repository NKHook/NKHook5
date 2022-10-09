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
				std::filesystem::path imagePath;
				std::vector<Animation*> animations;
				std::vector<Cell*> cells;
			public:
				FrameInfo();
				FrameInfo(std::string name, TexType type, bool required = true);
				FrameInfo(std::string name, TexType type, size_t texW, size_t texH, bool required = true);
				FrameInfo(std::string name, TexType type, size_t texW, size_t texH, std::filesystem::path imagePath, bool required = true);
				FrameInfo(std::string name, TexType type, size_t texW, size_t texH, std::filesystem::path imagePath, std::vector<Animation*> animations, std::vector<Cell*> cells, bool required = true);
			public:
				static FrameInfo* FromNode(std::filesystem::path docPath, rapidxml::xml_node<>*, std::string name, TexType type);
				static FrameInfo* Create(
					std::string name,
					TexType type,
					size_t texW,
					size_t texH,
					bool required = true
				);

				size_t GetTexWidth();
				size_t GetTexHeight();
				const std::filesystem::path& GetImagePath();
				const std::vector<Animation*>& GetAnimations();
				const std::vector<Cell*>& GetCells();

				void AddCell(Cell* toAdd);
				void AddAnimation(Animation* toAdd);

				rapidxml::xml_node<>* ToXML(rapidxml::xml_document<>* document);
			};
		}
	}
}