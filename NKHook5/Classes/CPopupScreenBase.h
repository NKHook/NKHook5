#ifndef NKHOOK5_CLASSES_CPOPUPSCREENBASE
#define NKHOOK5_CLASSES_CPOPUPSCREENBASE

#include "Macro.h"
#include "CBloonsBaseScreen.h"
#include "CBasePositionableObject.h"

namespace NKHook5
{
	using namespace Signatures;

	namespace Classes
	{
		class CPopupScreenBase : public CBloonsBaseScreen
		{
		public:
			char pad_00EC[80]; //0x00EC
			class CBasePositionableObject* pRootObj; //0x013C
			char pad_0140[280]; //0x0140
		public:
			CPopupScreenBase(CGameSystemPointers* pCGameSystemPointers, ghstl::string* screenName) : CBloonsBaseScreen(screenName, pCGameSystemPointers) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CGameSystemPointers*, ghstl::string*>(Sigs::CPopupScreenBase_CCTOR, this, pCGameSystemPointers, screenName);
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