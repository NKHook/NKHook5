#pragma once

#include "CBaseFactory.h"
#include "CBloon.h"
#include "CFlagStringConvertor.h"
#include "SBloonInfo.h"

namespace NKHook5::Classes
{
	class CBloonFactory : public CBaseFactory<SBloonInfo, CBloon>, public CFlagStringConvertor
	{
	public:
	};
	static_assert(sizeof(CBaseFactory<SBloonInfo, CBloon>) == 0x50);
	static_assert(sizeof(CFlagStringConvertor) == 0xC);
	static_assert(sizeof(CBloonFactory) == 0x5C);
}
