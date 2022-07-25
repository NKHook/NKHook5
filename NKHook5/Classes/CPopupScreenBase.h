#ifndef NKHOOK5_CLASSES_CPOPUPSCREENBASE
#define NKHOOK5_CLASSES_CPOPUPSCREENBASE

#include "Macro.h"
#include "CBloonsBaseScreen.h"
#include "CBasePositionableObject.h"

namespace NKHook5
{
	namespace Signatures {
		namespace CPopupScreenBase {
			static const char* SIG_CCTOR = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 56 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 ?? 75 ?? ?? 75 ?? ?? 45 ?? ?? ?? ?? ?? 8D ?? ?? ?? ?? ?? 50";
			static const char* SIG_ADDOBJECT = "55 8B EC 53 8B D9 B8 67 ?? ?? ?? 8B";
		}
	};

	namespace Classes
	{
		class CPopupScreenBase : public CBloonsBaseScreen
		{
		private:
			char pad_00D4[384]; //0x00D4
		public:
			CPopupScreenBase(CGameSystemPointers* pCGameSystemPointers, ghstl::string* screenName) : CBloonsBaseScreen(screenName, pCGameSystemPointers) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CGameSystemPointers*, ghstl::string*>(Signatures::CPopupScreenBase::SIG_CCTOR, this, pCGameSystemPointers, screenName);
			}
			void AddObject(CBasePositionableObject* object, int param_1) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CBasePositionableObject*, int>(Signatures::CPopupScreenBase::SIG_ADDOBJECT, this, object, param_1);
			}
			virtual ~CPopupScreenBase() {};
		};

		static_assert(sizeof(CPopupScreenBase) == 0x0254);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CPOPUPSCREENBASE */