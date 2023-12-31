#pragma once

#include "../Util/NewFramework.h"
#include "Macro.h"

#include "CStatusEffect.h"
#include "CSprite.h"
#include "CTextureManager.h"

namespace NKHook5::Classes
{
#define CNapalmStatusEffect_VFuncCount 9
	class CNapalmStatusEffect : public CStatusEffect, public CCompoundSprite
	{
	public:
		overload_allocators;

		class CTextureManager* mTexMgr; //0x0170
		class CBaseFileIO* mFileIO; //0x0174
		float mDamageInterval; //0x0178
		float mDamageTimer; //0x017C

		CNapalmStatusEffect(CTextureManager* texMgr, float damageRate, float damageTimer = 0.0f) : CStatusEffect(), CCompoundSprite({0,0}, nullptr, nullptr)
		{
			this->mTexMgr = texMgr;
			this->mDamageInterval = damageRate;
			this->mDamageTimer = damageTimer;
		}

	}; //Size: 0x014C
	static_assert(sizeof(CNapalmStatusEffect) == 0x180);
}