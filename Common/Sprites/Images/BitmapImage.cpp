#include "BitmapImage.h"
#include "../../Logging/Logger.h"

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;

BitmapImage::BitmapImage() {
	this->bmpColors = std::vector<std::vector<uint32_t>>();
	this->width = 0;
	this->height = 0;
}

BitmapImage::BitmapImage(std::vector<uint32_t> bmpColors, size_t width, size_t height) {
	std::vector<std::vector<uint32_t>> splitColors = std::vector<std::vector<uint32_t>>(width, std::vector<uint32_t>(height));
	size_t fullLen = width + height;
	if (fullLen >= bmpColors.size()) {
		Print("The width and height of the BitmapImage is creater than the data given!");
		throw std::exception("The width and height of the BitmapImage is creater than the data given!");
	}
	size_t idx;
	for (size_t x = 0; x < width; x++) {
		for (size_t y = 0; y < height; y++) {
			splitColors[x][y] = bmpColors[idx];
			idx++;
		}
	}
	this->bmpColors = bmpColors;
	this->width = width;
	this->height = height;
}

BitmapImage::BitmapImage(std::vector<std::vector<uint32_t>> bmpColors, size_t width, size_t height) {
	this->bmpColors = bmpColors;
	this->width = width;
	this->height = height;
}

size_t BitmapImage::GetWidth() {
	return this->width;
}

size_t BitmapImage::GetHeight() {
	return this->height;
}

uint32_t BitmapImage::At(size_t x, size_t y) {
	return this->bmpColors[x][y];
}

std::vector<uint32_t> BitmapImage::ColorBytes() {
	std::vector<uint32_t> result;
	for (size_t x = 0; x < this->GetWidth(); x++) {
		for (size_t y = 0; y < this->GetHeight(); y++) {
			result.push_back(this->At(x, y));
		}
	}
	return result;
}