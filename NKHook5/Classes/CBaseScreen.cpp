#include "CBaseScreen.h"
#include "CPopupScreenBase.h"

#include "Macro.h"

using namespace NKHook5;
using namespace NKHook5::Classes;

void CBaseScreen::OpenPopup(CPopupScreenBase* popupScreen, IScreenData* popupData, uint32_t* param_3) {
	ThisCall<void, CBaseScreen*, CPopupScreenBase*, IScreenData*, uint32_t*>(Signatures::CBaseScreen::SIG_OPENPOPUP, this, popupScreen, popupData, param_3);
};