#pragma once

#include "IBasePointers.h"
#include "CTowerFactory.h"
#include "CPlayerProfileV1.h"

namespace NKHook5::Classes
{
	class CGameSystemPointers : public IBasePointers
	{
	public:
		class CBloonManager* mBloonMgr = nullptr; //0x0070
		class CWeaponTaskManager* mWeaponTaskMgr = nullptr; //0x0074
		class CTowerManager* mTowerMgr = nullptr; //0x0078
		char pad_007C[4]; //0x007C
		class CPathManager* mPathMgr = nullptr; //0x0080
		class CAircraftManager* mAircraftMgr = nullptr; //0x0084
		class CManualWeaponManager* mManualWeaponMgr = nullptr; //0x0088
		char pad_008C[8]; //0x008C
		class CDailyQuestManager* mDailyQuestMgr = nullptr; //0x0094
		char pad_0098[4]; //0x0098
		class CTowerFactory* mTowerFactory = nullptr; //0x009C
		char pad_00A0[32]; //0x00A0
		class CPlayerProfileV1* mProfile = nullptr; //0x00C0
		char pad_00C4[40]; //0x00C4


	public:
		virtual ~CGameSystemPointers() = default;
	};
	static_assert(sizeof(CGameSystemPointers) == 0xEC);
	static_assert(offsetof(CGameSystemPointers, mProfile) == 0xC0);
} // namespace NKHook5::Classes
