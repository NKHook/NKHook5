#pragma once

#include "CBaseTower.h"
#include "CBloon.h"
#include "SGameTime.h"

#include "../Util/NewFramework.h"

namespace NKHook5
{
	namespace Classes
	{
		class CStatusEffect
		{
		public:
			overload_new;

		public:
			CBloon* bloon; //0x0004
			char pad_0008[16]; //0x0008
			CBaseTower* tower; //0x0018
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

		static_assert(sizeof(CStatusEffect) == 0x28);
	}
}