#include "CLImage.h"

using namespace Common;
using namespace Common::Graphics;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;

CLImage::CLImage()
{
	this->gpuImage = 0;
	this->width = 0;
	this->height = 0;
}

CLImage::CLImage(std::vector<uint32_t> bmpColors, size_t width, size_t height)
{
	this->gpuImage = CLImg::MakeImage(bmpColors, width, height);
	this->width = width;
	this->height = height;
}

CLImage::CLImage(std::vector<std::vector<uint32_t>> bmpColors, size_t width, size_t height)
{
	std::vector<uint32_t> colorBytes;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			colorBytes.push_back(bmpColors[x][y]);
		}
	}
	this->gpuImage = CLImg::MakeImage(colorBytes, width, height);
	this->width = width;
	this->height = height;
}

CLImage::CLImage(cl_mem gpuImage, size_t width, size_t height)
{
	this->gpuImage = gpuImage;
	this->width = width;
	this->height = height;
}

size_t CLImage::GetWidth()
{
	return this->width;
}

size_t CLImage::GetHeight()
{
	return this->height;
}

uint32_t CLImage::At(size_t x, size_t y)
{
	return CLImg::GetColorAt(this->gpuImage, x, y);
}

std::vector<uint32_t> CLImage::ColorBytes()
{
	return CLImg::ColorsFromCL(this->gpuImage, this->width, this->height);
}
