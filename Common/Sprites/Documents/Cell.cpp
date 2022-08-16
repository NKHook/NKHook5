#include "Cell.h"

#include "../../Graphics/CLImg.h"

using namespace Common;
using namespace Common::Graphics;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

void Cell::ExtractImage() {
	if (!this->fullImage) {
		Print(LogLevel::ERR, "Cannot extract a cell as the full image is nullptr!");
		return;
	}
	cl_mem gpuImage = CLImg::MakeImage(this->fullImage);
	this->image = CLImg::NewImageFromCL(gpuImage, this->x, this->y, this->w, this->h);
}

Cell::Cell() : InfoBase() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->ax = 0;
	this->ay = 0;
	this->aw = 0;
	this->ah = 0;
	this->fullImage = nullptr;
	this->image = nullptr;
}

Cell::Cell(std::string name,
	size_t x,
	size_t y,
	size_t w,
	size_t h,
	size_t ax,
	size_t ay,
	size_t aw,
	size_t ah) : InfoBase(name)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->ax = ax;
	this->ay = ay;
	this->aw = aw;
	this->ah = ah;
	this->fullImage = nullptr;
	this->image = nullptr;
}

Cell::Cell(std::string name,
	size_t x,
	size_t y,
	size_t w,
	size_t h,
	size_t ax,
	size_t ay,
	size_t aw,
	size_t ah,
	BitmapImage* fullImage) : InfoBase(name)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->ax = ax;
	this->ay = ay;
	this->aw = aw;
	this->ah = ah;
	this->fullImage = fullImage;
	this->image = nullptr;
	this->ExtractImage();
}

BitmapImage* Cell::ExtractedImage() {
	if (this->image == nullptr) {
		if (this->fullImage == nullptr) {
			Print(LogLevel::ERR, "Tried to get a cell's extracted image but the fullImage was null!");
			return nullptr;
		}
		this->ExtractImage();
	}
	return this->image;
}