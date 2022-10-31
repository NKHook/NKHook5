#pragma once

#include "../Classes/CGameSystemPointers.h"
#include "../Classes/CTextObject.h"
#include "../Classes/CPopupScreenBase.h"
#include "../Classes/Macro.h"
#include <polyhook2/Detour/ADetour.hpp>

namespace NKHook5 {
	namespace ClassesEx {
		class CModListScreen : public Classes::CPopupScreenBase {
			void** pVanillaVTable = nullptr;
		public:
			static void __fastcall InitLayout(CModListScreen* self, size_t pad, Classes::IScreenData* pScreenData);

			CModListScreen(Classes::CGameSystemPointers* pCGSP) : Classes::CPopupScreenBase(pCGSP, "ModListScreen")
			{
				//Get the vtables here
				void*** ppVanillaVTable = (void***)Signatures::GetAddressOf(Sigs::CPopupScreenBase_VTable);
				this->pVanillaVTable = *ppVanillaVTable;

				void*** ppCustomVTable = (void***)this;

				//Copy the vanilla funcs to this vtable
				
				//Keep track of funcs we don't want replaced

				//Change our vtable's protection (the 33 is the num of virtual funcs)
				DWORD oprot = 0;
				VirtualProtect(*ppCustomVTable, sizeof(size_t) * CPopupScreenBase_VFuncCount, PAGE_EXECUTE_READWRITE, &oprot);

				//Write the vanilla vtable to our custom vtable
				memcpy(*ppCustomVTable, *ppVanillaVTable, sizeof(size_t) * CPopupScreenBase_VFuncCount);

				//Place back the funcs we dont want replaced
				(*ppCustomVTable)[2] = &CModListScreen::InitLayout;

				//Now we have our own vtable overridden by the game's vtable, and we are free to make changes.
			}

			virtual void ButtonPressed(Classes::SButtonCB& callback) override {

			}
		};
	}
}