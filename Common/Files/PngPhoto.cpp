#ifdef _WIN32
#include <Windows.h>
#include <Unknwn.h>
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>
#include <gdiplusimaging.h>
#include "../Graphics/GdiUtil.h"
#endif

#include "PngPhoto.h"
#include "../Logging/Logger.h"
#include "../Sprites/Images/BitmapImage.h"

using namespace Common;
using namespace Common::Files;
using namespace Common::Files::Images;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
namespace fs = std::filesystem;

PngPhoto::PngPhoto() : Photo() {
	this->image = nullptr;
}

PngPhoto::PngPhoto(fs::path path) : Photo(path) {
	this->image = nullptr;
}

bool PngPhoto::Open(fs::path path) {
	return this->OpenRead(path);
}
bool PngPhoto::OpenRead(fs::path path) {
	Photo::OpenRead(path);

	Gdiplus::Bitmap gdiBmp(path.wstring().c_str());

	size_t width = gdiBmp.GetWidth();
	size_t height = gdiBmp.GetHeight();

	Gdiplus::Rect r(0, 0, width, height);

	Gdiplus::BitmapData bmpData;
	gdiBmp.LockBits(&r, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData);

	uint32_t* colorBytes = (uint32_t*)bmpData.Scan0;
	std::vector<uint32_t> imgData;
	for (size_t i = 0; i < width * height; i++) {
		imgData.push_back(colorBytes[i]);
	}

	gdiBmp.UnlockBits(&bmpData);

	BitmapImage* memImg = new BitmapImage(imgData, width, height);
	this->image = memImg;

	return true;
}
bool PngPhoto::OpenWrite(fs::path path) {
	return Photo::OpenWrite(path);;
}

Images::Image* PngPhoto::ReadImg() {
	return this->image;
}

void PngPhoto::WriteImg(Images::Image* image) {
	Photo::WriteImg(image);

	size_t width = image->GetWidth();
	size_t height = image->GetHeight();
	std::vector<uint32_t> colors = image->ColorBytes();

	Gdiplus::Bitmap gdiBmp(width, height, PixelFormat32bppARGB);

	for (size_t x = 0; x < width; x++) {
		for (size_t y = 0; y < height; y++) {
			uint32_t colorData = image->At(x, y);
			Gdiplus::Color gdiColor(colorData);
			gdiBmp.SetPixel(x, y, gdiColor);
		}
	}

	CLSID encoderClsid;
	Gdiplus::GetEncoderClsid(L"image/png", &encoderClsid);

	Gdiplus::Status error = gdiBmp.Save(this->GetPath().lexically_normal().c_str(), &encoderClsid);
	if (error == Gdiplus::Win32Error) {
		size_t gle = GetLastError();
		Print("Last error: %d (%x)", gle, gle);
	}
}