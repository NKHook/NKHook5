#ifndef NKHOOK5_CLASSES_CBASESCREEN
#define NKHOOK5_CLASSES_CBASESCREEN

#include "../Utils.h"
#include "Macro.h"
#include "IBasePointers.h"
#include "IScreenData.h"
#include <ghstl/string>

namespace NKHook5
{
	namespace Signatures {
		namespace CBaseScreen {
			static const char* SIG_CCTOR = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F9 ?? 7D ?? 8D ?? ?? E8 ?? ?? ?? ?? ?? 45";
			static const char* SIG_OPENPOPUP = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 53 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? ?? 0F ?? ?? ?? 8B F1 ?? 75 ?? 8B";
		};
	};

	namespace Classes
	{
		enum class Device {
			PHONE = 0,
			TABLET = 1,
			UNKNOWN = 2
		};

		class CBaseScreen : public IBasePointers
		{
		public:
			CBaseScreen(ghstl::string* screenName) {
				ThisCall<void, CBaseScreen*, ghstl::string*>(Signatures::CBaseScreen::SIG_CCTOR, this, screenName);
			};
			void OpenPopup(class CPopupScreenBase* popupScreen, IScreenData* popupData, uint32_t* param_3);
			virtual ~CBaseScreen() {};
		};
	} // namespace Classes

} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_CBASESCREEN */
