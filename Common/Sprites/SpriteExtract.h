#pragma once

#include "Documents/SpriteTable.h"

namespace Common {
	namespace Sprites {
		using namespace Common;
		using namespace Common::Sprites;
		using namespace Common::Sprites::Documents;

		class SpriteExtract {
			SpriteTable* table;
			std::filesystem::path resultDir;
		public:
			SpriteExtract(SpriteTable* table);
			void SetResult(std::filesystem::path resultDir);
			void ExtractAll();
		};
	}
}