#pragma once

#include "CBaseTower.h"
#include "CBloon.h"
#include "SGameTime.h"

#include "../Util/NewFramework.h"

namespace NKHook5
{
	namespace Classes
	{
#pragma pack(push, 1)
		class CStatusEffect
		{
		public:
			overload_new;

		public:
			//char pad_0000[4]; //0x0000
			class CBloon* bloon; //0x0004
			bool frozen; //0x0008
			bool N00001EF0; //0x0009
			bool N00001EF3; //0x000A
			bool N00001EF1; //0x000B
			float duration; //0x000C
			float timeRemaining; //0x0010
			bool clear; //0x0014
			bool N00001EE9; //0x0015
			bool N00001EEC; //0x0016
			bool N00001EEA; //0x0017
			class CBaseTower* tower; //0x0018
			char pad_001C[12]; //0x001C

		public:
			virtual ~CStatusEffect() {};
			virtual CStatusEffect* Clone() = 0;
			virtual int TypeID() = 0;
			virtual void Apply() = 0;
			virtual void Reset() = 0;
			virtual void Update(SGameTime& time) = 0;
			virtual void Render() = 0;
			virtual float GetBloonSpeed(float base) { return base; };
			virtual void IncreasePops(int amount) {};
		};
#pragma pack(pop)

		static_assert(sizeof(CStatusEffect) == 0x28);
	}
}