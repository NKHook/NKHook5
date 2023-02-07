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
			char pad_0254[44]; //0x0254
			CBaseButton* displayButton; //0x0280
			char pad_0284[4]; //0x0284
			CSpriteButton* controlsButton; //0x0288
			CTextObject* controlsButtonText; //0x028C
			CMainButton* languageButton; //0x0290
			CBasePositionableObject* languageGroup; //0x0294
			CBasePositionableObject* controlsGroup; //0x0298

		public:
			CSettingsScreen(CGameSystemPointers* pCGameSystemPointers) {
				ThisCall<CSettingsScreen*, CSettingsScreen*, CGameSystemPointers*>(Sigs::CSettingsScreen_CCTOR, this, pCGameSystemPointers);
			}

			virtual ~CSettingsScreen() {};
		};

		static_assert(sizeof(CSettingsScreen) == 0x29C);
		static_assert(offsetof(CSettingsScreen, controlsGroup) == 0x298);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CSETTINGSSCREEN */