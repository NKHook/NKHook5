#pragma once

#include "Photo.h"
#include "../Sprites/Images/BitmapImage.h"

namespace Common {
	namespace Files {
		using namespace Common;
		using namespace Common::Sprites;

		class PngPhoto : public Photo {
			BitmapImage* image = nullptr;
		public:
			PngPhoto();
			PngPhoto(std::filesystem::path path);

			virtual bool Open(std::filesystem::path) override;
			virtual bool OpenRead(std::filesystem::path) override;
			virtual bool OpenWrite(std::filesystem::path) override;

			virtual Image* ReadImg() override;
			virtual void WriteImg(Image*) override;
		};
	}
}