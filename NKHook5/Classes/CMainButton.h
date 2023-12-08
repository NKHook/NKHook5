#pragma once

#include "CBaseScreen.h"
#include "CInput.h"
#include "CSpriteButton.h"
#include "CTextObject.h"
#include "IButtonDelegate.h"
#include "SMainButtonStyle.h"
#include "SSpriteInfo.h"

#include "../../Util/NewFramework.h"
#include "Macro.h"

namespace NKHook5::Classes {
	class CMainButton : public CSpriteButton {
	public:
		overload_allocators

	public:
		char pad_01D4[24]; //0x01D4
		class CTextObject* buttonText; //0x01EC
		class SMainButtonStyle style; //0x01F0
		char pad_0248[8]; //0x0248
	public:
		CMainButton() {

		}
		CMainButton(CInput* input, IButtonDelegate* screen, std::string buttonName, std::string buttonText, SSpriteInfo* param_5, SSpriteInfo* param_6, SMainButtonStyle style) {
			ThisConstruct<Sigs::CMainButton_CCTOR>(this, input, screen, buttonName, buttonText, param_5, param_6, style);
		}
	};

	static_assert(sizeof(CMainButton) == 0x250);
	static_assert(offsetof(CMainButton, buttonText) == 0x1EC);
}