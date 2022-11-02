#ifndef NKHOOK5_CLASSES_CSETTINGSSCREEN
#define NKHOOK5_CLASSES_CSETTINGSSCREEN

#include "Macro.h"
#include "CBaseButton.h"
#include "CBasePositionableObject.h"
#include "CPopupScreenBase.h"

namespace NKHook5
{
	namespace Classes
	{
		using namespace Signatures;

		class CSettingsScreen : public CPopupScreenBase
		{
		public:
			char pad_0258[40]; //0x0258
			class CBaseButton* displayButton; //0x0280
			char pad_0284[8]; //0x0284
			class CSpriteButton* controlsButton; //0x028C
			class CTextObject* controlsButtonText; //0x0290
			class CMainButton* languageButton; //0x0294
			class CBasePositionableObject* languageButton_1; //0x0298
			class CBasePositionableObject* menu_root; //0x029C

		public:
			CSettingsScreen(CGameSystemPointers* pCGameSystemPointers) {
				ThisCall<CSettingsScreen*, CSettingsScreen*, CGameSystemPointers*>(Sigs::CSettingsScreen_CCTOR, this, pCGameSystemPointers);
			}

			virtual ~CSettingsScreen() {};
		};

		static_assert(sizeof(CSettingsScreen) == 0x2A0);
		static_assert(offsetof(CSettingsScreen, menu_root) == 0x29C);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CSETTINGSSCREEN */