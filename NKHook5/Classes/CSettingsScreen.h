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
			CBaseButton* displayButton; //0x0280
			char pad_0284[24]; //0x0284
			CBasePositionableObject* parentObj; //0x029C

			CSettingsScreen(CGameSystemPointers* pCGameSystemPointers) {
				ThisCall<CSettingsScreen*, CSettingsScreen*, CGameSystemPointers*>(Sigs::CSettingsScreen_CCTOR, this, pCGameSystemPointers);
			}

			virtual ~CSettingsScreen() {};
		};

		static_assert(sizeof(CSettingsScreen) == 0x2A0);
		static_assert(offsetof(CSettingsScreen, parentObj) == 0x29C);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CSETTINGSSCREEN */