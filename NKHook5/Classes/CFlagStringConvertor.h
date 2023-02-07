#pragma once

#include "../../Util/NewFramework.h"

namespace NKHook5 {
	namespace Classes {
		class CFlagStringConvertor
		{
		public:
			char pad_0000[12]; //0x0000
		}; //Size: 0x000C

		static_assert(sizeof(CFlagStringConvertor) == 0xC);
	}
}