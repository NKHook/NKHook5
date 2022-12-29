#pragma once

#include "CBasePositionableObject.h"
#include "CGameSystemPointers.h"

namespace NKHook5 {
	namespace Classes {
		enum DrawLayer {
			ABOVE_TOWERS,
			BELOW_TOWERS
		};

		class CWeaponTask : public CBasePositionableObject {
		public:
			char pad_00A8[44]; //0x00A8
			DrawLayer drawLayer; //0x00D4
			char pad_00D8[40]; //0x00D8
			CGameSystemPointers* gamePtrs; //0x0100
			char pad_0104[32]; //0x0104

		public:
			/* CWeapon VT funcs */
			virtual CWeaponTask* Clone() { return nullptr; };
			virtual void* FUN_006ffed0(uint32_t param_2) { return nullptr; };
			virtual void* FUN_006fff50() { return nullptr; };
			virtual void* FUN_007096b0(uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5) { return nullptr; };
			virtual void FUN_OPTIMIZEDOUT(class SGameTime* pSGameTime) {};
			virtual void Kill() {};
		};

		static_assert(sizeof(CWeaponTask) == 0x124);
	}
}