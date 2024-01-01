#pragma once

#include "../../Util/NewFramework.h"
#include "CSprite.h"
#include "SCompoundSprite.h"

#include <vector>

namespace NKHook5::Classes {
	class CCompoundSprite : public CSprite
	{
	public:
		overload_allocators

	public:
		CBasePositionableObject* N00001ABB{}; //0x0104
		char pad_0108[4]{}; //0x0108
		std::vector<CSprite*> sprites; //0x010C
		char pad_0118[12]; //0x0118
		class CAnimationSystem* mAnimationSystem = nullptr; //0x0124
		class SCompoundSprite* mSpriteDef = nullptr; //0x0128
		char pad_012C[28]; //0x012C

		CCompoundSprite(Vec2F v, SCompoundSprite* info, class CEventManager* eventManager) : CSprite(nullptr, false, v, true)
		{
			ThisConstruct<Sigs::CCompoundSprite_CCTOR, CCompoundSprite>(this, &v, info, eventManager);
		}

		void _Load(const SCompoundSprite* info, bool a, bool b)
		{
			ThisCall_NonMember<Sigs::CCompoundSprite_Load, void, CCompoundSprite>(this, info, &a, &b);
		}

		void Load(SCompoundSprite* info, bool a, bool b)
		{
			if(info != nullptr)
			{
				this->mSpriteDef = info;
				this->_Load(info, a, b);
			}
		}

	public:
		virtual void* GetName() { return nullptr; };
	}; //Size: 0x0148

	static_assert(sizeof(CCompoundSprite) == 0x148);
}