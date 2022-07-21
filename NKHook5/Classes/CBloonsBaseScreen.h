#ifndef NKHOOK5_CLASSES_CBLOONSBASESCREEN
#define NKHOOK5_CLASSES_CBLOONSBASESCREEN

#include "CGameSystemPointers.h"
#include "CBaseScreen.h"
#include "Macro.h"

namespace NKHook5
{
	namespace Signatures {
		namespace CBloonsBaseScreen {
			static const char* SIG_CCTOR = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F9 ?? 7D ?? 8D ?? ?? E8 ?? ?? ?? ?? ?? 45";
		};
	};

	namespace Classes
	{
		class CBloonsBaseScreen : public CBaseScreen
		{
		public:
		public:
			CBloonsBaseScreen(ghstl::string* screenName, CGameSystemPointers* pCGameSystemPointers) : CBaseScreen(screenName)  {
				ThisCall<void, CBloonsBaseScreen*, ghstl::string*, CGameSystemPointers*>(Signatures::CBloonsBaseScreen::SIG_CCTOR, this, screenName, pCGameSystemPointers);
			}
			virtual ~CBloonsBaseScreen() {};
		};
	} // namespace Classes

} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_CBLOONSBASESCREEN */
