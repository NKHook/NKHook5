#include "Process.h"

#include "../../Classes/CFont.h"
#include "../../Classes/CFontManager.h"
#include "../../Classes/CSettingsScreen.h"
#include "../../ClassesEx/CSettingsScreenExt.h"
#include "../../Classes/CTextObject.h"
#include "../../Classes/CBloonsTD5Game.h"
#include "../../Classes/CScreenManager.h"
#include "../../Classes/ScriptedScreen.h"
#include "../../Classes/ScriptedScreenData.h"
#include "../../Classes/Vec2F.h"
#include "../../Utils.h"
#include "../../Signatures/Signature.h"

#include <Util/Macro.h>


namespace NKHook5::Patches::CSettingsScreen
{
	using namespace Signatures;

	static uint64_t o_func;
	static void __fastcall cb_hook(ClassesEx::CSettingsScreenExt* self, int pad, Classes::SGameTime* gameTime) {
	}

	auto Process::Apply() -> bool
	{
		const void* address = Signatures::GetAddressOf(Sigs::CSettingsScreen_Process);
		if(address)
		{
			auto* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
			if(detour->hook())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
} // namespace CBasePositionableObject