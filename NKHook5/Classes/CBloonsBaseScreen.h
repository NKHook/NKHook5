#ifndef NKHOOK5_CLASSES_CBLOONSBASESCREEN
#define NKHOOK5_CLASSES_CBLOONSBASESCREEN

#include "../../Util/NewFramework.h"
#include "boost/shared_ptr"
#include "CAssetBag.h"
#include "CBaseScreen.h"
#include "CBasePositionableObject.h"
#include "CFont.h"
#include "CGameSystemPointers.h"
#include "Macro.h"
#include <vector>

namespace NKHook5
{
	using namespace Signatures;

	namespace Classes
	{
		class CBloonsBaseScreen : public CBaseScreen
		{
		public:
			CGameSystemPointers* pCGameSystemPointers; //0x00B8
			char pad_00BC[12]; //0x00BC
			boost::shared_ptr<CFont> pMenuFont; //0x00C8
			char pad_00D0[4]; //0x00D0
			std::vector<CBasePositionableObject*> elements; //0x00D4
			char pad_00E0[8]; //0x00E0
		public:
			CBloonsBaseScreen(ghstl::string* screenName, CGameSystemPointers* pCGameSystemPointers) : CBaseScreen(screenName)  {
				ThisCall<void, CBloonsBaseScreen*, ghstl::string*, CGameSystemPointers*>(Sigs::CBloonsBaseScreen_CCTOR, this, screenName, pCGameSystemPointers);
			}
			virtual ~CBloonsBaseScreen() {};
		};

		static_assert(sizeof(CBloonsBaseScreen) == 0x00EC);
		static_assert(offsetof(CBloonsBaseScreen, pMenuFont) == 0x00CC);
	} // namespace Classes

} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_CBLOONSBASESCREEN */
