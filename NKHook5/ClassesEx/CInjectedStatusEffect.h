#pragma once

#include "../Util/NewFramework.h"

#include "../Classes/CCompoundSprite.h"
#include "../Classes/CGlueStatusEffect.h"
#include "../Classes/CNapalmStatusEffect.h"

namespace NKHook5
{
	using namespace NKHook5::Classes;
	namespace ClassesEx
	{
		class CInjectedStatusEffect : public CNapalmStatusEffect
		{
		public:
			overload_allocators;

			float mSpeedScale = 1.0f; //0x002C
			bool mAdjustedGraphic = false;
			uint64_t mInjectedId = 0;
			nfw::string mGraphicName;
			bool mExceptMoab = false;
			void** mpVanillaVTable = nullptr;

			CInjectedStatusEffect(uint64_t injectedId, nfw::string graphicName, bool exceptMoab, CTextureManager* texMgr, float damageRate, float damageTimer = 0.0f, float speedScale = 1.0f);
		};
	}
}