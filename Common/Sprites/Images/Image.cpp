#include "Image.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;

Image::Image() {

}

size_t Image::GetWidth() {
	return 0;
}

size_t Image::GetHeight() {
	return 0;
}

uint32_t Image::At(size_t x, size_t y) {
	return 0;
}

static std::vector<uint32_t> empty;
const std::vector<uint32_t>& Image::ColorBytes() {
	return empty;
}