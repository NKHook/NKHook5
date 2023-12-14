#include "CBaseScreen.h"
#include "CPopupScreenBase.h"

#include "Macro.h"

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::Signatures;


void CBaseScreen::OpenPopup(CPopupScreenBase* popupScreen, IScreenData* popupData, const uint32_t* param_3) {
	ThisCall<Sigs::CBaseScreen_OpenPopup, &CBaseScreen::OpenPopup>(this, popupScreen, popupData, param_3);
};

void CBaseScreen::_OpenPopup(CPopupScreenBase* popupScreen, IScreenData* popupData) {
	uint32_t param_3_holder = 0;
	this->OpenPopup(popupScreen, popupData, &param_3_holder);
};

void CBaseScreen::StartUsingAsset(const CAssetBag::eAssetType& type, const nfw::string& assetName) {
	if (this->mAssetBag == nullptr) {
		//FUCK FUCK FUCK FUCK
		return;
	}
	this->mAssetBag->StartUsing(type, assetName);
}

CBaseScreen* CBaseScreen::GetScreen(const nfw::string& screenName) {
	return ThisCall<Sigs::CBaseScreen_GetScreen, &CBaseScreen::GetScreen>(this, screenName);
}