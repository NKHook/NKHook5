#include "CBaseScreen.h"
#include "CPopupScreenBase.h"

#include "Macro.h"

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::Signatures;

void CBaseScreen::OpenPopup(CPopupScreenBase* popupScreen, IScreenData* popupData) {
	uint32_t param_3_holder = 0;
	ThisCall<void, CBaseScreen*, CPopupScreenBase*, IScreenData*, uint32_t*>(Sigs::CBaseScreen_OpenPopup, this, popupScreen, popupData, &param_3_holder);
};

void CBaseScreen::OpenPopup(CPopupScreenBase* popupScreen, IScreenData* popupData, uint32_t* param_3) {
	ThisCall<void, CBaseScreen*, CPopupScreenBase*, IScreenData*, uint32_t*>(Sigs::CBaseScreen_OpenPopup, this, popupScreen, popupData, param_3);
};

void CBaseScreen::StartUsingAsset(eAssetType type, std::string& assetName) {
	ThisCall<void, CBaseScreen*, eAssetType*, std::string&>(Sigs::CBaseScreen_StartUsingAsset, this, &type, assetName);
}