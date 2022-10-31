#include "CModListScreen.h"

#include "../Classes/CScreenManager.h"

using namespace NKHook5;
using namespace NKHook5::ClassesEx;

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
	Classes::CBaseScreen* mainMenu = self->basePointers.pCScreenManager->GetScreen("MainMenuScreen");
	void** menuvft = *(void***)mainMenu;
	auto oddfunc = (void(__thiscall*)(CBaseScreen*))menuvft[26];
	oddfunc(mainMenu);
}
