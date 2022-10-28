#pragma once

#include "Macro.h"
#include "CBloonsBaseScreen.h"
#include "CBasePositionableObject.h"
#include "CMainButton.h"
#include "CToggleButton.h"
#include "IButtonDelegate.h"
#include "SMainButtonStyle.h"
#include "Vec2F.h"

#include <string>

namespace NKHook5
{
	using namespace Signatures;

	namespace Classes
	{
		enum class eNavButtonType {
			CLOSE = 0xF,
		};

		class CPopupScreenBase : public CBloonsBaseScreen, public IButtonDelegate
		{
		public:
			char pad_010C[48]; //0x010C
			CBasePositionableObject* pRootObj; //0x013C
			char pad_0140[184]; //0x0140
			SMainButtonStyle buttonStyle; //0x01F8
			char pad_0254[4]; //0x0254
		public:
			CPopupScreenBase() : CBloonsBaseScreen() {

			};
			CPopupScreenBase(CGameSystemPointers* pCGameSystemPointers, std::string screenName) : CBloonsBaseScreen() {
				ThisCall<CPopupScreenBase*, CPopupScreenBase*, CGameSystemPointers*, std::string&>(Sigs::CPopupScreenBase_CCTOR, this, pCGameSystemPointers, screenName);
			}
			virtual ~CPopupScreenBase() {};

			virtual void DrawForeground() {}
			virtual CMainButton* CreateDebugButton(std::string param_1, std::string iconSprite, std::string buttonSprite, std::string param_4, Vec2F& param_5) { return nullptr; }
			virtual CMainButton* CreateButton(std::string param_1, std::string param_2, std::string param_3, std::string param_4, Vec2F& position) { return nullptr; }
			virtual CMainButton* CreateButton_1(std::string param_1, std::string param_2, std::string param_3, std::string param_4, Vec2F& position) { return nullptr; }
			virtual CMainButton* CreateButtonBasic(std::string param_1, std::string param_2, std::string param_3, std::string param_4, Vec2F& position) { return nullptr; }
			virtual CMainButton* CreateButtonBasic_1(std::string param_1, std::string param_2, std::string param_3, std::string param_4, Vec2F& position) { return nullptr; }
			virtual CToggleButton* CreateButtonToggle(std::string param_1, std::string param_2, std::string param_3, std::string param_4, std::string param_5, bool param_6, Vec2F& param_7, Vec2F& param_8) { return nullptr; }
			virtual CToggleButton* CreateButtonToggle_1(std::string param_1, std::string param_2, std::string param_3, std::string param_4, std::string param_5, bool param_6, Vec2F& param_7, Vec2F& param_8) { return nullptr; }
			virtual void ChangeState(int eScreenSubState) {}


			void AddObject(CBasePositionableObject* object, int param_1) {
				ThisCall<void, CPopupScreenBase*, CBasePositionableObject*, int>(Sigs::CPopupScreenBase_AddObject, this, object, param_1);
			}
			void AddNavButton(eNavButtonType type, std::string icon) {
				ThisCall<void, CPopupScreenBase*, eNavButtonType, std::string>(Sigs::CPopupScreenBase_AddNavButton, this, type, icon);
			}
		};

		static_assert(sizeof(CPopupScreenBase) == 0x0258);
		static_assert(offsetof(CPopupScreenBase, pRootObj) == 0x13C);
	} // namespace Classes

} // namespace NKHook5
