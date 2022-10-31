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

		class CSettingsScreen : public CPopupScreenBase
		{
		public:
			char pad_0258[68]; //0x0258
			class CBasePositionableObject* parentObj; //0x029C
			char pad_02A0[4]; //0x02A0

			CSettingsScreen(CGameSystemPointers* pCGameSystemPointers) {
				ThisCall<CSettingsScreen*, CSettingsScreen*, CGameSystemPointers*>(Sigs::CSettingsScreen_CCTOR, this, pCGameSystemPointers);
			}

			virtual ~CSettingsScreen() {};
		};

		static_assert(sizeof(CSettingsScreen) == 0x2A4);
		static_assert(offsetof(CSettingsScreen, parentObj) == 0x29C);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CSETTINGSSCREEN */