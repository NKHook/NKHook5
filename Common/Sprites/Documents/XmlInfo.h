#pragma once

#include "../Images/BitmapImage.h"
#include "FrameInfo.h"

#include <filesystem>
#include <string>
#include <vector>

namespace Common {
	namespace Sprites {
		namespace Documents {
			using namespace Common;
			using namespace Common::Sprites;
			using namespace Common::Sprites::Images;

			class XmlInfo : public SpriteInfo {
				std::vector<FrameInfo*> frames;
			public:
				XmlInfo();
				XmlInfo(std::string name, TexType type);
				XmlInfo(std::string name, TexType type, std::vector<FrameInfo*> frames);
			public:
				static XmlInfo* ReadDoc(std::filesystem::path path, std::string name, TexType type);
				const std::vector<FrameInfo*>& GetFrames();
			};
		}
	}
}