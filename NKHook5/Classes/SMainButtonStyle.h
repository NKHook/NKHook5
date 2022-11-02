#pragma once

#include "boost/shared_ptr"
#include "CFont.h"
#include "Macro.h"

#include <string>

namespace NKHook5 {
	namespace Classes {
		struct SMainButtonStyle {
			boost::shared_ptr<CFont> font;
			char pad_0008[8]; //0x0008
			Vec3F position; //0x0010
			std::string primarySheet; //0x001C
			std::string secondarySheet; //0x0034
			char pad_004C[12]; //0x004C

		public:
			SMainButtonStyle() {
				ThisCall<void, SMainButtonStyle*>(Sigs::SMainButtonStyle_CCTOR, this);
			}
			SMainButtonStyle(SMainButtonStyle& rhs) {
				ThisCall<void, SMainButtonStyle*, SMainButtonStyle&>(Sigs::SMainButtonStyle_CopyCCTOR, this, rhs);
			}
		};

		static_assert(sizeof(SMainButtonStyle) == 0x58);
	}
}