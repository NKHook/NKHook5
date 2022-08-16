#ifdef _WIN32
#include <Windows.h>
#include <Unknwn.h>
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>
#include <gdiplusimaging.h>
#include "GdiEncoder.h"
#endif

#include "BmpPhoto.h"
#include "../Sprites/Images/BitmapImage.h"

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

	HDC memHdc = CreateCompatibleDC(NULL);

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
	DeleteDC(memHdc);

	BitmapImage* memImg = new BitmapImage(imgData, width, height);
	this->image = memImg;

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

	HDC memHdc = CreateCompatibleDC(NULL);
	Gdiplus::Bitmap gdiBmp(this->GetPath().wstring().c_str());

	size_t width = image->GetWidth();
	size_t height = image->GetHeight();

	for (size_t x = 0; x < width; x++) {
		for (size_t y = 0; y < height; y++) {
			uint32_t colorData = image->At(x, y);
			Gdiplus::Color gdiColor(colorData);
			gdiBmp.SetPixel(x, y, gdiColor);
		}
	}

	CLSID encoderClsid;
	Gdiplus::GetEncoderClsid(L"image/bmp", &encoderClsid);

	gdiBmp.Save(this->GetPath().wstring().c_str(), &encoderClsid, NULL);
}