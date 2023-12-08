#pragma once

#include "CBasePositionableObject.h"
#include "CBloonEscapedEvent.h"
#include "CModifierStack.h"
#include "CObserver.h"
#include "CTowerRemovedEvent.h"

#include "../Util/NewFramework.h"

namespace NKHook5::Classes
{
	class CBaseTower :
		public CBasePositionableObject,
		public CObserver<CBloonEscapedEvent>,
		public CObserver<CTowerRemovedEvent>
	{
	public:
		overload_allocators;

	public:
		char pad_00B8[4]; //0x00B8
		class CGameSystemPointers* mGameSystemPointers = nullptr; //0x00BC
		char pad_00C0[4]; //0x00C0
		int32_t mRefCount; //0x00C4
		char pad_00C8[8]; //0x00C8
		uint64_t mTypeFlags; //0x00D0
		char pad_00D8[20]; //0x00D8
		int32_t mPopCount; //0x00EC
		bool mSelected; //0x00F0
		bool mSellable; //0x00F1
		bool N00002453; //0x00F2
		bool mUpgradable; //0x00F3
		char pad_00F4[16]; //0x00F4
		class CCompoundSprite* mSprite = nullptr; //0x0104
		uint32_t mColor; //0x0108
		char pad_010C[12]; //0x010C
		bool mFiring; //0x0118
		char pad_0119[11]; //0x0119
		float mLifetime; //0x0124
		float mAliveTime; //0x0128
		bool mPleaseDestroy; //0x012C
		char pad_012D[11]; //0x012D
		int32_t mLeftUpgrades; //0x0138
		int32_t mRightUpgrades; //0x013C
		int32_t N00000F4E; //0x0140
		int32_t mSellPrice; //0x0144
		CModifierStack mModifierStack; //0x0148
		char pad_015C[36]; //0x015C
		uint64_t mTargetingFlags; //0x0180
		char pad_0188[140]; //0x0188
		bool N00000F82; //0x0214
		bool mHovered; //0x0215
		char pad_0216[10]; //0x0216

	public:
		~CBaseTower() override = default;

		virtual void OnRemove() {};
		virtual int GetPopCount() { return this->mPopCount; };
		virtual void SetPopCount(int popCount) { this->mPopCount = popCount; };
		virtual void IncPopCount(int amount, class CBloon* bloon) {};
		virtual void KONG_FUN_00633bb0() {};
	};

	static_assert(sizeof(CObserver<CBloonEscapedEvent>) == 0x8);
	static_assert(sizeof(CObserver<CTowerRemovedEvent>) == 0x8);
	static_assert(sizeof(CBaseTower) == 0x220);
} // namespace NKHook5::Classes

