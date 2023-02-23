#pragma once

#include "Photo.h"
#include "../Sprites/Images/MTImage.h"

namespace Common {
	namespace Files {
		using namespace Common;
		using namespace Common::Sprites;

		class BmpPhoto : public Photo {
			MTImage* image = nullptr;
		public:
			BmpPhoto();
			BmpPhoto(std::filesystem::path path);

			virtual bool Open(std::filesystem::path) override;
			virtual bool OpenRead(std::filesystem::path) override;
			virtual bool OpenWrite(std::filesystem::path) override;

			virtual MTImage* ReadImg() override;
			virtual void WriteImg(MTImage*) override;
		};
	}
}