#pragma once

#include "../Classes/CCompoundSprite.h"
#include "../Classes/CStatusEffect.h"

namespace NKHook5
{
	using namespace NKHook5::Classes;
	namespace ClassesEx
	{
		class CSpriteStatusEffect :
			public CStatusEffect,
			public CCompoundSprite
		{
		public:
			CSpriteStatusEffect();
			virtual ~CSpriteStatusEffect();
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