#ifndef NKHOOK5_CLASSES_CBLOONSBASESCREEN
#define NKHOOK5_CLASSES_CBLOONSBASESCREEN

#include "../../Util/Allocators.h"
#include "boost/shared_ptr"
#include "CAssetBag.h"
#include "CBaseScreen.h"
#include "CBasePositionableObject.h"
#include "CFont.h"
#include "CGameSystemPointers.h"
#include "Macro.h"
#include <ghstl/vector>

namespace NKHook5
{
	using namespace Signatures;

	namespace Classes
	{
		class CBloonsBaseScreen : public CBaseScreen
		{
		public:
			char pad_00B0[4]; //0x00B0
			boost::shared_ptr<CAssetBag> pCAssetBag; //0x00B4
			CGameSystemPointers* pCGameSystemPointers; //0x00BC
			char pad_00C0[12]; //0x00C0
			boost::shared_ptr<CFont> pMenuFont; //0x00CC
			char pad_00D4[4]; //0x00D4
			ghstl::vector<CBasePositionableObject*> elements; //0x00D8
			char pad_00E4[8]; //0x00E4
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
