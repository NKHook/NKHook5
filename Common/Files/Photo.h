#pragma once

#include "File.h"
#include <Sprites/Images/MTImage.h>

namespace Common {
	namespace Files {
		using namespace Sprites;
		using namespace Sprites::Images;

		class Photo : public File {
			MTImage image;
			bool writeMode;
		public:
			Photo();
			Photo(std::filesystem::path path);

			virtual bool Open(std::filesystem::path) override;
			virtual bool OpenRead(std::filesystem::path) override;
			virtual bool OpenWrite(std::filesystem::path) override;

			virtual MTImage ReadImg();
			virtual void WriteImg(MTImage image);
		};
	}
}