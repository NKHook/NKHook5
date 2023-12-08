#pragma once

#include "../../Util/NewFramework.h"

namespace NKHook5::Classes {
	class CFlagStringConvertor
	{
	public:
		char pad_0000[12]; //0x0000

		nfw::string FlagToString(uint32_t category, uint64_t flag);
	}; //Size: 0x000C

	static_assert(sizeof(CFlagStringConvertor) == 0xC);
}
