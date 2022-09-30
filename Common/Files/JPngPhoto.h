#pragma once

#include "Photo.h"
#include "../Sprites/Images/CLImage.h"

namespace Common {
	namespace Files {
		using namespace Common;
		using namespace Common::Sprites;

		class JPngPhoto : public Photo {
			CLImage* pngImage = nullptr;
			CLImage* jpegImage = nullptr;
		public:
			JPngPhoto();
			JPngPhoto(std::filesystem::path path);

			virtual bool Open(std::filesystem::path) override;
			virtual bool OpenRead(std::filesystem::path) override;
			virtual bool OpenWrite(std::filesystem::path) override;

			virtual Image* ReadImg() override;
			virtual void WriteImg(Image*) override;
		};
	}
}