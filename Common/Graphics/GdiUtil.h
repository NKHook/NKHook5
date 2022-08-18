#pragma once

#include <Windows.h>
#include <Unknwn.h>
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>
#include <gdiplusimaging.h>

namespace Gdiplus {
	void SetupGDI();
	void StopGDI();
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	Bitmap* ImageToBitmap(Image* img, Color bkgd = Color::Transparent);
}