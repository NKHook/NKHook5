#include "BitmapImage.h"
#include "../../Logging/Logger.h"

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;

BitmapImage::BitmapImage() {
	this->colorBytes = std::vector<uint32_t>();
	this->width = 0;
	this->height = 0;
}

BitmapImage::BitmapImage(std::vector<uint32_t> bmpColors, size_t width, size_t height) {
	//std::vector<std::vector<uint32_t>> splitColors = std::vector<std::vector<uint32_t>>(width, std::vector<uint32_t>(height));
	/*size_t fullLen = width * height;
	if (fullLen > bmpColors.size()) {
		Print("The width and height of the BitmapImage is greater than the data given!");
		throw std::exception("The width and height of the BitmapImage is greater than the data given!");
	}
	size_t idx = 0;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			splitColors[x][y] = bmpColors[idx];
			idx++;
		}
	}*/
	this->colorBytes = bmpColors;
	this->width = width;
	this->height = height;
}

BitmapImage::BitmapImage(std::vector<std::vector<uint32_t>> bmpColors, size_t width, size_t height) {
	std::vector<uint32_t> colorBytes;
	for (size_t y = 0; y < this->GetHeight(); y++) {
		for (size_t x = 0; x < this->GetWidth(); x++) {
			colorBytes.push_back(bmpColors[x][y]);
		}
	}
	this->colorBytes = colorBytes;
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
	return this->colorBytes[(y*width)+x];
}

const std::vector<uint32_t>& BitmapImage::ColorBytes() {
	return this->colorBytes;
	/*std::vector<uint32_t> result;
	for (size_t y = 0; y < this->GetHeight(); y++) {
		for (size_t x = 0; x < this->GetWidth(); x++) {
			result.push_back(this->At(x, y));
		}
	}
	return result;*/
}