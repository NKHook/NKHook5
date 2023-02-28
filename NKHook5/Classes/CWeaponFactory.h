#pragma once

#include "CBaseFactory.h"
#include "CFlagStringConvertor.h"
#include "CWeapon.h"
#include "JsonObject.h"

namespace NKHook5 {
	namespace Classes {
		class CWeaponFactory : public CBaseFactory<struct SWeaponInfo, CWeapon>, public CFlagStringConvertor
		{
		public:
			JsonObject currentDocument;
		};
	}
}