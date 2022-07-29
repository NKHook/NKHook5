#ifndef NKHOOK5_CLASSES_CSETTINGSSCREEN
#define NKHOOK5_CLASSES_CSETTINGSSCREEN

#include "Macro.h"
#include "CBasePositionableObject.h"
#include "CPopupScreenBase.h"

namespace NKHook5
{
	namespace Classes
	{
		using namespace Signatures;

		ghstl::string* settingScreen = new ghstl::string("SettingsScreen");
		class CSettingsScreen : public CPopupScreenBase
		{
		public:
			char pad_0254[68]; //0x0254
			class CBasePositionableObject* parentObj; //0x0298
			char pad_029C[4]; //0x029C

			CSettingsScreen(CGameSystemPointers* pCGameSystemPointers) : CPopupScreenBase(pCGameSystemPointers, settingScreen) {
				ThisCall<CSettingsScreen*, CSettingsScreen*, CGameSystemPointers*>(Sigs::CSettingsScreen_CCTOR, this, pCGameSystemPointers);
			}

			virtual ~CSettingsScreen() {};
		};

		static_assert(sizeof(CSettingsScreen) == 0x2A0);
		static_assert(offsetof(CSettingsScreen, parentObj) == 0x298);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CSETTINGSSCREEN */