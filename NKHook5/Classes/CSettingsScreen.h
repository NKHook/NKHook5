#pragma once

#include "Macro.h"
#include "CBaseButton.h"
#include "CBasePositionableObject.h"
#include "CPopupScreenBase.h"

namespace NKHook5::Classes
{
	using namespace Signatures;

	class CSettingsScreen : public CPopupScreenBase
	{
	public:
		char pad_0254[32]{}; //0x0254
		class CToggleButton* mMusicButton = nullptr; //0x0274
		class CToggleButton* mSoundButton = nullptr; //0x0278
		class CSpriteButton* mDrmButton = nullptr; //0x027C
		class CBaseButton* mDisplayButton = nullptr; //0x0280
		char pad_0284[4]{}; //0x0284
		class CSpriteButton* mControlsButton = nullptr; //0x0288
		class CTextObject* mControlsButtonText = nullptr; //0x028C
		class CMainButton* mLanguageButton = nullptr; //0x0290
		class CBasePositionableObject* mLanguageGroup = nullptr; //0x0294
		class CBasePositionableObject* mControlsGroup = nullptr; //0x0298

	public:
		explicit CSettingsScreen(CGameSystemPointers* pCGameSystemPointers) {
			ThisConstruct<Sigs::CSettingsScreen_CCTOR>(this, pCGameSystemPointers);
		}

		~CSettingsScreen() override = default;
	};

	static_assert(sizeof(CSettingsScreen) == 0x29C);
	static_assert(offsetof(CSettingsScreen, mControlsGroup) == 0x298);
} // namespace NKHook5::Classes