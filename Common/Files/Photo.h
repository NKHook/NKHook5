#pragma once

#include "File.h"
#include <Sprites/Images/MTImage.h>

namespace Common::Files {
	using namespace Sprites;
	using namespace Sprites::Images;

	class Photo : public File {
		bool writeMode;
	public:
		Photo();
		explicit Photo(std::filesystem::path path);

		bool Open(std::filesystem::path) override;
		bool OpenRead(std::filesystem::path) override;
		bool OpenWrite(std::filesystem::path) override;

		virtual MTImage* ReadImg();
		virtual void WriteImg(MTImage* image);
	};
}