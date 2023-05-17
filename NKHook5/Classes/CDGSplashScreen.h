#pragma once

#include "Macro.h"
#include "CBaseButton.h"
#include "CBasePositionableObject.h"
#include "CBloonsBaseScreen.h"
#include "CCompoundSprite.h"

namespace NKHook5
{
	namespace Classes
	{
		using namespace Signatures;

		class CDGSplashScreen : public CBloonsBaseScreen
		{
		public:
			char pad_00D0[12]; //0x00D0
			CCompoundSprite* splashSprite; //0x00DC
		public:
			virtual ~CDGSplashScreen() {};
		};
	} // namespace Classes

} // namespace NKHook5