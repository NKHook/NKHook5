#include "MTImage.h"

#include <Logging/Logger.h>
#include <Threading/WorkGroup.h>

#include <mutex>
#include <string>

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
using namespace Common::Logging::Logger;
using namespace Common::Threading;

MTImage::MTImage()
{
	this->width = 0;
	this->height = 0;
}

MTImage::MTImage(const std::vector<uint32_t>& bmpColors, size_t width, size_t height)
{
	this->colors = bmpColors;
	this->width = width;
	this->height = height;
}

MTImage::MTImage(const std::vector<std::vector<uint32_t>>& bmpColors, size_t width, size_t height)
{
	std::vector<uint32_t> colorBytes;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			colorBytes.push_back(bmpColors[x][y]);
		}
	}
	this->colors = colorBytes;
	this->width = width;
	this->height = height;
}

MTImage::~MTImage()
{
}

size_t MTImage::GetWidth() const
{
	return this->width;
}

size_t MTImage::GetHeight() const
{
	return this->height;
}

uint32_t MTImage::At(size_t x, size_t y) const
{
	return this->colors.at((x * width) + y);
}

std::vector<uint32_t> MTImage::ColorBytes()
{
	return this->colors;
}

MTImage MTImage::CopyImage() {
	return this->CopyImage(this->GetWidth(), this->GetHeight());
}
MTImage MTImage::CopyImage(size_t width, size_t height) {
	return this->CopyImage(0, 0, width, height);
}
MTImage MTImage::CopyImage(size_t x, size_t y, size_t width, size_t height) {
	std::vector<uint32_t> colors(width * height);
	for (size_t ix = x; ix < width; ix++)
	{
		for (size_t iy = y; iy < height; iy++)
		{
			colors[(iy - y) + ((ix - x) * width)] = this->At(ix, iy);
		}
	}
	return MTImage(colors, width - x, height - y);
}

bool MTImage::PasteImage(const MTImage& other, size_t x, size_t y, int32_t width, int32_t height) {
	for (size_t ix = x; ix < width; ix++)
	{
		for (size_t iy = y; iy < height; iy++)
		{
			this->colors[(iy - y) + ((ix - x) * width)] = other.At(ix, iy);
		}
	}
	return true;
}

bool MTImage::PasteChannel(const MTImage& other, int channel)
{
	if (this->GetWidth() != other.GetWidth())
	{
		throw std::exception("Width of source and target images do not match in PasteChannel!");
	}
	if (this->GetHeight() != other.GetHeight())
	{
		throw std::exception("Height of source and target images do not match in PasteChannel!");
	}

	for (size_t x = 0; x < this->GetWidth(); x++)
	{
		for (size_t y = 0; y < this->GetHeight(); y++)
		{
			uint32_t otherCol = other.At(x, y);
			char* otherChans = (char*)&otherCol;

			uint32_t thisCol = this->At(x, y);
			char* thisChans = (char*)&thisCol;

			thisChans[channel] = otherChans[channel];

			this->colors[y + (x * width)] = thisCol;
		}
	}
}