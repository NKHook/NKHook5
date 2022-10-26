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

#include <string>
#include <vector>

namespace NKHook5
{
	using namespace Signatures;

	namespace Classes
	{
		class CBloonsBaseScreen : public CBaseScreen
		{
		public:
			CGameSystemPointers* pCGameSystemPointers; //0x00BC
			char pad_00C0[12]; //0x00C0
			boost::shared_ptr<CFont> pMenuFont; //0x00CC
		public:
			CBloonsBaseScreen() : CBaseScreen() {

			}
			CBloonsBaseScreen(std::string screenName, CGameSystemPointers* pCGameSystemPointers) : CBaseScreen(screenName)  {
				ThisCall<void, CBloonsBaseScreen*, std::string&, CGameSystemPointers*>(Sigs::CBloonsBaseScreen_CCTOR, this, screenName, pCGameSystemPointers);
			}
			virtual ~CBloonsBaseScreen() {};
		};

		static_assert(sizeof(CBloonsBaseScreen) == 0x00D4);
		static_assert(offsetof(CBloonsBaseScreen, pMenuFont) == 0x00CC);
	} // namespace Classes

} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_CBLOONSBASESCREEN */
