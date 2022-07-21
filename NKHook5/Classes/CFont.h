#pragma once

#include "CReferenceCounted.h"
#include <ghstl/string>

namespace NKHook5 {
	namespace Classes {
		class CFont : public CReferenceCounted {
		public:
			char pad_0004[16]; //0x0004
			ghstl::string fontName; //0x0014
			char pad_002C[24]; //0x002C
		public:
			virtual ~CFont() {};
		};
	}
}