#pragma once

#include "XmlInfo.h"
#include <filesystem>
#include <string>
#include <vector>

namespace Common {
	namespace Sprites {
		namespace Documents {
			class SpriteTable {
				std::vector<XmlInfo*> spriteXmls;
				SpriteTable();
				SpriteTable(std::vector<XmlInfo*>);
			public:
				static SpriteTable* ReadTable(std::filesystem::path tableFile);
			};
		}
	}
}