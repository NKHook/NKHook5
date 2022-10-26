#pragma once

#include <string>

namespace NKHook5 {
	namespace Classes {
		struct SMainButtonStyle {
			char pad_0000[28]; //0x0000
			std::string primarySheet; //0x001C
			std::string secondarySheet; //0x0034
			char pad_004C[16]; //0x004C
		};

		static_assert(sizeof(SMainButtonStyle) == 0x5C);
	}
}