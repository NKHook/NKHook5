#pragma once

#include "../Classes/CGameSystemPointers.h"
#include "../Classes/CTextObject.h"
#include "../Classes/CPopupScreenBase.h"
#include "../Classes/Macro.h"

#include <polyhook2/Detour/ADetour.hpp>

namespace NKHook5::ClassesEx {
	class CModListScreen : public Classes::CPopupScreenBase {
		void** pVanillaVTable = nullptr;
	public:
		static void __fastcall InitLayout(CModListScreen* self, size_t pad, Classes::IScreenData* pScreenData);
		static void __fastcall Hide(CModListScreen* self);

		explicit CModListScreen(Classes::CGameSystemPointers* pointers);

		void ButtonPressed(Classes::CBaseButton* callback) override;
	};
}