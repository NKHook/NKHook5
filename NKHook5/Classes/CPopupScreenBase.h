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
			char pad_00EC[76]; //0x00EC
			CBasePositionableObject* pRootObj; //0x0138
			char pad_013C[280]; //0x013C
		public:
			CPopupScreenBase(CGameSystemPointers* pCGameSystemPointers, ghstl::string* screenName) : CBloonsBaseScreen(screenName, pCGameSystemPointers) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CGameSystemPointers*, ghstl::string*>(Sigs::CPopupScreenBase_CCTOR, this, pCGameSystemPointers, screenName);
			}
			void AddObject(CBasePositionableObject* object, int param_1) {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CBasePositionableObject*, int>(Sigs::CPopupScreenBase_AddObject, this, object, param_1);
			}
			virtual ~CPopupScreenBase() {};
		};

		static_assert(sizeof(CPopupScreenBase) == 0x0254);
		static_assert(offsetof(CPopupScreenBase, pRootObj) == 0x138);
	} // namespace Classes

} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CPOPUPSCREENBASE */