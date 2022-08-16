#pragma once

#include "File.h"
#include "../Sprites/Images/Image.h"

namespace Common {
	namespace Files {
		using namespace Sprites;
		using namespace Sprites::Images;

		class Photo : public File {
			Image* image;
			bool writeMode;
		public:
			Photo();
			Photo(std::filesystem::path path);

			virtual bool Open(std::filesystem::path) override;
			virtual bool OpenRead(std::filesystem::path) override;
			virtual bool OpenWrite(std::filesystem::path) override;

			virtual Image* ReadImg();
			virtual void WriteImg(Image*);
		};
	}
}