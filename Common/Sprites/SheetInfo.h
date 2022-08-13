#pragma once

#include "FrameInfo.h"
#include "XmlInfo.h"
#include <memory>
#include <vector>

namespace Common {
	namespace Sprites {
		class SheetInfo {
			std::vector<FrameInfo> frames;
			std::vector<XmlInfo> xmlFiles;
		public:
			SheetInfo(std::vector<FrameInfo> frames);
			static std::shared_ptr<SheetInfo> Parse(std::string data);
		};
	}
}