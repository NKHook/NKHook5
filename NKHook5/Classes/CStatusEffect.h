#pragma once

#include "CBaseTower.h"
#include "CBloon.h"
#include "SGameTime.h"

#include "Macro.h"
#include "../Util/NewFramework.h"


namespace NKHook5::Classes
{
#pragma pack(push, 1)
	class CStatusEffect
	{
	public:
		overload_allocators;

	public:
		//char pad_0000[4]; //0x0000
		class CBloon* mBloon; //0x0004
		bool mFrozen; //0x0008
		bool N00001EF0; //0x0009
		bool N00001EF3; //0x000A
		bool N00001EF1; //0x000B
		float mDuration; //0x000C
		float mTimer; //0x0010
		bool mClear; //0x0014
		bool N00001EE9; //0x0015
		bool N00001EEC; //0x0016
		bool N00001EEA; //0x0017
		class CBaseTower* mTower; //0x0018
		char pad_001C[8]; //0x001C
		bool mIgnoreImmunity; //0x0024
		char pad_0025[3]; //0x0025

	public:
		virtual ~CStatusEffect() {};
		virtual CStatusEffect* Clone() { return nullptr; };
		virtual uint64_t TypeID() { return 0; };
		virtual void Apply() {};
		virtual void Reset() {};
		virtual void Update(SGameTime& time) {};
		virtual void Render() {};
		virtual float GetBloonSpeed(float base) { return base; };
		virtual void IncreasePops(int amount) {};

		void IncTowerRef(CBaseTower* tower)
		{
			return ThisCall<Sigs::CStatusEffect_IncTowerRef, &CStatusEffect::IncTowerRef>(this, tower);
		}
	};
#pragma pack(pop)

	static_assert(sizeof(CStatusEffect) == 0x28);
}
