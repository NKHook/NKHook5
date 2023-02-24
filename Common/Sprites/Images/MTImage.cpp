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

#define _AT(x, y) (x) + ((y) * width)
#define _ATW(x, y, wid) (x) + ((y) * wid)

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
	std::vector<uint32_t> colorBytes(width * height);
#pragma omp parallel for collapse(2)
	for (int64_t y = 0; y < height; y++) {
		for (int64_t x = 0; x < width; x++) {
			colorBytes[_ATW(x, y, width)] = bmpColors[x][y];
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
	return this->colors.at(_AT(x, y));
}

std::vector<uint32_t> MTImage::ColorBytes()
{
	return this->colors;
}

MTImage* MTImage::CopyImage() {
	return this->CopyImage(this->GetWidth(), this->GetHeight());
}
MTImage* MTImage::CopyImage(size_t width, size_t height) {
	return this->CopyImage(0, 0, width, height);
}
MTImage* MTImage::CopyImage(size_t x, size_t y, size_t width, size_t height) {
	std::vector<uint32_t> resultBytes(width * height);
#pragma omp parallel for
	for (int64_t row = 0; row < height; row++) {
		uint32_t* row_ptr = &this->colors[_ATW(x, y + row, this->width)];
		memcpy(&resultBytes[_AT(0, row)], row_ptr, width * sizeof(uint32_t));
	}
	return new MTImage(resultBytes, width, height);
}

bool MTImage::PasteImage(const MTImage* other, size_t x, size_t y, int32_t width, int32_t height) {
	if (width == -1)
		width = other->GetWidth();
	if (height == -1)
		height = other->GetHeight();

	if (this->colors.size() < width * height)
		this->colors = std::vector<uint32_t>(width * height);

#pragma omp parallel for
	for (int64_t row = 0; row < height; row++) {
		uint32_t* dest_ptr = &this->colors[_ATW(x, y + row, this->width)];
		memcpy(dest_ptr, &other->colors[_AT(0, row)], width * sizeof(uint32_t));
	}
	return true;
}

bool MTImage::PasteChannel(const MTImage* other, int channel)
{
	if (this->GetWidth() != other->GetWidth())
	{
		throw std::exception("Width of source and target images do not match in PasteChannel!");
	}
	if (this->GetHeight() != other->GetHeight())
	{
		throw std::exception("Height of source and target images do not match in PasteChannel!");
	}

#pragma omp parallel for
	for (int i = 0; i < this->colors.size(); i++)
	{
		uint32_t otherCol = other->colors[i];
		char* otherChans = (char*)&otherCol;

		uint32_t thisCol = this->colors[i];
		char* thisChans = (char*)&thisCol;

		thisChans[channel] = otherChans[channel];

		this->colors[i] = thisCol;
	}
}