#include "GdiUtil.h"
#include "../Logging/Logger.h"

#include <memory>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

static ULONG_PTR gdiplusToken = 0;

void Gdiplus::SetupGDI() {
	if (gdiplusToken != 0) {
		Print(LogLevel::DEBUG, "GDI cannot be started since its already started (gdiplusToken was not 0)!");
		return;
	}
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void Gdiplus::StopGDI() {
	if (gdiplusToken == 0) {
		Print(LogLevel::DEBUG, "GDI cannot be stopped since there is no gdiplus token!");
		return;
	}
	GdiplusShutdown(gdiplusToken);
}

int Gdiplus::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	using namespace Gdiplus;
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

Gdiplus::Bitmap* Gdiplus::ImageToBitmap(Gdiplus::Image* img, Gdiplus::Color bkgd)
{
	Gdiplus::Bitmap* bmp = nullptr;
	try {
		int wd = img->GetWidth();
		int hgt = img->GetHeight();
		auto format = img->GetPixelFormat();
		bmp = new Gdiplus::Bitmap(wd, hgt, format);
		auto g = std::unique_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromImage(bmp));
		g->Clear(bkgd);
		g->DrawImage(img, 0, 0, wd, hgt);
	}
	catch (std::exception& ex) {
		Print(LogLevel::ERR, "Error converting image to bitmap: %s", ex.what());
	}
	if (bmp) {
		if (bmp->GetLastStatus() != Gdiplus::Status::Ok) {
			Print(LogLevel::ERR, "Image::GetLastStatus was NOT ok: %d (%x)", bmp->GetLastStatus(), bmp->GetLastStatus());
		}
	}
	return bmp;
}