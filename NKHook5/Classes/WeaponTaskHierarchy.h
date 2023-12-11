#pragma once

#include "CWeaponTask.h"

namespace NKHook5::Classes::WeaponTaskHierarchy
{
	struct SNode
	{
		char pad_0000[16]; //0x0000
		Classes::CWeaponTask* resultTask = nullptr; //0x0010
	};
}