#ifndef NKHOOK5_CLASSES_CPOPUPSCREENBASE
#define NKHOOK5_CLASSES_CPOPUPSCREENBASE

#include "Macro.h"
#include "CBloonsBaseScreen.h"
#include "CBasePositionableObject.h"
#include "IButtonDelegate.h"
#include "SMainButtonStyle.h"

#include <string>

namespace NKHook5
{
	using namespace Signatures;

	namespace Classes
	{
		class CPopupScreenBase : public CBloonsBaseScreen, public IButtonDelegate
		{
		public:
			char pad_010C[48]; //0x010C
			CBasePositionableObject* pRootObj; //0x013C
			char pad_0140[184]; //0x0140
			SMainButtonStyle buttonStyle; //0x01F8
			char pad_0254[4]; //0x0254
		public:
			CPopupScreenBase() : CBloonsBaseScreen() {

			};
			CPopupScreenBase(CGameSystemPointers* pCGameSystemPointers, std::string screenName) : CBloonsBaseScreen(screenName, pCGameSystemPointers) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CGameSystemPointers*, std::string&>(Sigs::CPopupScreenBase_CCTOR, this, pCGameSystemPointers, screenName);
			}
			void AddObject(CBasePositionableObject* object, int param_1) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CBasePositionableObject*, int>(Sigs::CPopupScreenBase_AddObject, this, object, param_1);
			}
			virtual ~CPopupScreenBase() {};
		};

		static_assert(sizeof(CPopupScreenBase) == 0x0258);
		static_assert(offsetof(CPopupScreenBase, pRootObj) == 0x13C);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CPOPUPSCREENBASE */