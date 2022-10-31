#pragma once

#include "Macro.h"

#include "CInput.h"
#include "IInput.h"
#include "SGameTime.h"

#include <string>

namespace NKHook5 {
	namespace Classes {
		class CBaseButton : public IInput {
		public:
			char pad_0004[4]; //0x0004
			class AABoundingBox2D* pAABoundingBox2D; //0x0008
			char pad_000C[36]; //0x000C
			CInput* pCInput; //0x0030
			char pad_0034[20]; //0x0034
			std::string buttonName; //0x0048
			char pad_0060[108]; //0x0060

		public:
			CBaseButton(CInput* input, std::string buttonName, size_t param_3 = 0) {
				ThisCall<void, CBaseButton*, CInput*, std::string&, size_t>(Sigs::CBaseButton_CCTOR, this, input, buttonName, param_3);
			}
		public:
			virtual ~CBaseButton() {};
			virtual void Input(SGameTime* param_2) {};
			virtual void RegisterListener(struct SButtonListener* param_2) {};
			virtual void SetClicked() {};
			virtual void SetPressed() {};
			virtual void SetReleased() {};
			virtual void SetDisabled(bool b) {};
			virtual void UpdateHitArea() {};
		};
	}
}