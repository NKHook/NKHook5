#pragma once

#include "../../Classes/CGameScreen.h"
#include "../../Classes/IScreenData.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5::Patches::CBloonsBaseScreen
{
	using namespace NKHook5;

	class Init : public IPatch
	{
		void cb_hook(Classes::IScreenData* pScreenData);
	public:
		Init() : IPatch("CBloonsBaseScreen::Init")
		{

		}
		auto Apply() -> bool override;
	};
} // namespace CGameScreen