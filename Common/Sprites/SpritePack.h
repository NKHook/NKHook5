#pragma once

#include "Documents/SpriteTable.h"

#include <filesystem>

namespace Common {
	namespace Sprites {
		using namespace Common;
		using namespace Common::Sprites;
		using namespace Common::Sprites::Documents;

		class SpritePack {
			SpriteTable* table;
			std::filesystem::path resultDir;
		public:
			SpritePack(SpriteTable* table);
			void SetResult(std::filesystem::path resultDir);
			void PackAll();
		};
	}
}