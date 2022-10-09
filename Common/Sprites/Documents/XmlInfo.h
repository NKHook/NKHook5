#pragma once

#include "FrameInfo.h"

#include <filesystem>
#include <string>
#include <vector>

namespace Common {
	namespace Sprites {
		namespace Documents {
			using namespace Common;
			using namespace Common::Sprites;

			class XmlInfo : public SpriteInfo {
				std::vector<FrameInfo*> frames;
			public:
				XmlInfo();
				XmlInfo(std::string name, TexType type);
				XmlInfo(std::string name, TexType type, std::vector<FrameInfo*> frames);
			public:
				static XmlInfo* Create(
					std::string name,
					TexType type
				);
				static XmlInfo* ReadDoc(std::filesystem::path path, std::string name, TexType type);
				const std::vector<FrameInfo*>& GetFrames();

				void AddFrame(FrameInfo*);

				rapidxml::xml_document<>* ToXML();
			};
		}
	}
}