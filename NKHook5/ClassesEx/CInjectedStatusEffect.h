#pragma once

#include "../Util/NewFramework.h"

#include "../Classes/CCompoundSprite.h"
#include "../Classes/CGlueStatusEffect.h"

namespace NKHook5
{
	using namespace NKHook5::Classes;
	namespace ClassesEx
	{
		class CInjectedStatusEffect : public CGlueStatusEffect
		{
		public:
			overload_new;

			CInjectedStatusEffect(CTextureManager* texMgr, bool unk, float speedScale, float damageRate, float damageTimer = 0.0f);
			virtual ~CInjectedStatusEffect();
			virtual CStatusEffect* Clone();
			virtual int TypeID();
			virtual void Apply();
			virtual void Reset();
			virtual void Update(SGameTime& time);
			virtual void Render();
			virtual float GetBloonSpeed(float base);
			virtual void IncreasePops(int amount);
		};
	}
}