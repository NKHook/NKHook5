#include "CModListScreen.h"

#include "../Classes/CScreenManager.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace NKHook5;
using namespace NKHook5::ClassesEx;

CModListScreen::CModListScreen(Classes::CGameSystemPointers* pointers) : Classes::CPopupScreenBase(pointers, "ModListScreen")
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
	(*ppCustomVTable)[5] = &CModListScreen::Hide;

	//Now we have our own vtable overridden by the game's vtable, and we are free to make changes.
}

void __fastcall CModListScreen::InitLayout(CModListScreen* self, size_t pad, Classes::IScreenData* pScreenData)
{
	//Get the original InitLayout function
	auto baseInitLayout = (void(__thiscall*)(CModListScreen*, Classes::IScreenData*))self->pVanillaVTable[2];
	//Call it
	baseInitLayout(self, pScreenData);

	//Do custom layout stuff
	self->AddNavButton(Classes::eNavButtonType::CLOSE, "");
}

void __fastcall CModListScreen::Hide(CModListScreen* self)
{
	self->screenState = Classes::eScreenState::HIDDEN;
	Classes::CBaseScreen* mainMenu = self->mScreenManager->GetScreen("MainMenuScreen");
	void** menuvft = *(void***)mainMenu;
	auto oddfunc = (void(__thiscall*)(CBaseScreen*))menuvft[26];
	oddfunc(mainMenu);
}

void CModListScreen::ButtonPressed(Classes::CBaseButton* callback) {

}