#pragma once

#include "CBaseFactory.h"
#include "CFlagStringConvertor.h"
#include "CWeapon.h"

namespace NKHook5::Classes {
	class CWeaponFactory : public CBaseFactory<struct SWeaponInfo, CWeapon>, public CFlagStringConvertor
	{
		char padding_005C[16]{};
	public:
	};
	static_assert(sizeof(CWeaponFactory) == 0x6C);
}
