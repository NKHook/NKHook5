#pragma once

#include "Macro.h"
#include "../Util/NewFramework.h"

#include "CCompoundSprite.h"
#include "CStatusEffect.h"
#include "SBloonInfo.h"

namespace NKHook5::Classes {
	class CBloon : public CCompoundSprite {
	public:
		overload_allocators;

	public:
		char pad_0148[180]{}; //0x0148
		SBloonInfo* mBloonDefinition = nullptr; //0x01FC
		char pad_0200[8]{}; //0x0200
		uint32_t mStatusImmunity{}; //0x0208
		uint32_t mDamageImmunity{}; //0x020C
		char pad_0210[4]{}; //0x0210
		uint32_t mDrawLayer{}; //0x0214
		char pad_0218[12]{}; //0x0218
		float mHealth{}; //0x0224
		char pad_0228[8]{}; //0x0228
		float mFakeProgress{}; //0x0230
		char pad_0234[24]{}; //0x0234
		uint32_t N000025CD{}; //0x024C
		char pad_0250[28]{}; //0x0250
		float mProgress{}; //0x026C
		Vec2F mVelocity{}; //0x0270
		Vec2F mLocation{}; //0x0278
		uint32_t mPathType{}; //0x0280
		float mTurnTimer{}; //0x0284
		char pad_0288[4]{}; //0x0288
		float mLastProgress{}; //0x028C
		char pad_0290[40]{}; //0x0290

	public:
		void ApplyEffect(class CStatusEffect* effect, bool damageMoabs)
		{
			return ThisCall<Sigs::CBloon_ApplyEffect>(&CBloon::ApplyEffect, this, effect, damageMoabs);
		}
	};

	static_assert(sizeof(CBloon) == 0x2B8);
}