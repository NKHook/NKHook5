#pragma once

#include "../../Util/NewFramework.h"

#include "CAssetBag.h"
#include "CBaseScreen.h"
#include "CBasePositionableObject.h"
#include "CFont.h"
#include "CGameSystemPointers.h"
#include "Macro.h"

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

namespace NKHook5::Classes
{
	using namespace Signatures;

	class CBloonsBaseScreen : public CBaseScreen
	{
	public:
		CGameSystemPointers* mGameSystemPointers; //0x00B8
		char pad_00BC[12]; //0x00BC
		boost::shared_ptr<CFont> mScreenFont; //0x00C8

	public:
		CBloonsBaseScreen() : CBaseScreen() {

		}
		CBloonsBaseScreen(const nfw::string& screenName, CGameSystemPointers* pCGameSystemPointers) : CBaseScreen(screenName)  {
			ThisConstruct<Sigs::CBloonsBaseScreen_CCTOR>(this, screenName, pCGameSystemPointers);
		}
		virtual ~CBloonsBaseScreen() {};
	};

	static_assert(sizeof(CBloonsBaseScreen) == 0x00D0);
	static_assert(offsetof(CBloonsBaseScreen, mScreenFont) == 0x00C8);
} // namespace NKHook5::Classes
