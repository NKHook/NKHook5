#pragma once

#include "../Classes/CGameSystemPointers.h"
#include "../Classes/CSettingsScreen.h"
#include "../Classes/CMainButton.h"

namespace NKHook5 {
	namespace ClassesEx {
		class CSettingsScreenExt : public Classes::CSettingsScreen {
		public:
			Classes::CMainButton* modsButton = nullptr;
		};
	}
}