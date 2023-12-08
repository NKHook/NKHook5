#pragma once

#include "../../Util/NewFramework.h"
#include <boost/shared_ptr.hpp>
#include "CFont.h"
#include "Macro.h"

#include <string>

namespace NKHook5 {
	namespace Classes {
		struct SMainButtonStyle {
			overload_allocators

		public:
			boost::shared_ptr<CFont> mFont;
			char pad_0008[8]{}; //0x0008
			Vec3F mPosition{}; //0x0010
			std::string mPrimarySheet; //0x001C
			std::string mSecondarySheet; //0x0034
			char pad_004C[12]{}; //0x004C

		public:
			SMainButtonStyle() {
				ThisConstruct<Sigs::SMainButtonStyle_CCTOR>(this);
			}
			SMainButtonStyle(const SMainButtonStyle& rhs) {
				ThisConstruct<Sigs::SMainButtonStyle_CopyCCTOR>(this, rhs);
			}
		};

		static_assert(sizeof(SMainButtonStyle) == 0x58);
	}
}