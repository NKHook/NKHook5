#pragma once

#include <Windows.h>

namespace Gdiplus {
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
}