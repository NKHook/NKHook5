#pragma once

#include "Macro.h"

#include "CGameSystemPointers.h"
#include "CPopupScreenBase.h"
#include "IButtonDelegate.h"

#include "../Signatures/Signature.h"

namespace NKHook5 {
	namespace Classes {
		using namespace NKHook5::Signatures;

		class ScriptedScreen : public CPopupScreenBase {
			char pad_0258[92]; //0x0258
		public:
			ScriptedScreen(CGameSystemPointers* pGamePtrs) : CPopupScreenBase()
			{
				ThisCall<ScriptedScreen*, ScriptedScreen*, CGameSystemPointers*>(Sigs::ScriptedScreen_CCTOR, this, pGamePtrs);
			}
			virtual void ButtonPressed(Classes::CBaseButton* callback) override {};
		};
	}
}