#include "BmpPhoto.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Files::Images;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
namespace fs = std::filesystem;

BmpPhoto::BmpPhoto() : Photo() {
	this->image = nullptr;
}

BmpPhoto::BmpPhoto(fs::path path) : Photo(path) {
	this->image = nullptr;
}

bool BmpPhoto::Open(fs::path path) {
	return this->OpenRead(path);
}
bool BmpPhoto::OpenRead(fs::path path) {
	Photo::OpenRead(path);

	int width = 0;
	int height = 0;
	int channels = 0;
	uint32_t* colorBytes = (uint32_t*)stbi_load(path.string().c_str(), &width, &height, &channels, 4);
	std::vector<uint32_t> imgData;
	for (size_t i = 0; i < width * height; i++) {
		imgData.push_back(colorBytes[i]);
	}

	this->image = new CLImage(imgData, width, height);

	return true;
}
bool BmpPhoto::OpenWrite(fs::path path) {
	return Photo::OpenWrite(path);;
}

Images::Image* BmpPhoto::ReadImg() {
	return this->image;
}

void BmpPhoto::WriteImg(Images::Image* image) {
	Photo::WriteImg(image);

	size_t width = image->GetWidth();
	size_t height = image->GetHeight();
	std::vector<uint32_t> colors = image->ColorBytes();

	stbi_write_bmp(this->GetPath().string().c_str(), width, height, 4, colors.data());
}