#pragma once

#include "../../Util/NewFramework.h"
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
		enum class ePopupType
		{
			UNINITIALIZED = 0,
			LOADING = 1,
			STATIC = 2,
			UNKNOWN_1 = 3,
			CLOSING = 4,
			TRANSITIONING = 5
		};
		enum class eNavButtonType {
			CLOSE = 0xF,
		};

#define CPopupScreenBase_VFuncCount 33
		class CPopupScreenBase : public CBloonsBaseScreen, public IButtonDelegate
		{
		public:
			/* Somehow prevented some heap corruption bug... */
			overload_allocators

		public:
			char pad_0108[20]{}; //0x0108
			class CBasePositionableObject* mRoot = nullptr; //0x011C
			class CBasePositionableObject* N00000182 = nullptr; //0x0120
			class CBasePositionableObject* mPopupControls = nullptr; //0x0124
			class CBasePositionableObject* mMidContent = nullptr; //0x0128
			class CColouredQuad* mBackgroundQuads[4]{}; //0x012C
			class CBuildingName* mTitle = nullptr; //0x013C
			char pad_0140[40]{}; //0x0140
			ePopupType mPopupState{}; //0x0168
			float mTimeOpened = 0.0f; //0x016C
			char pad_0170[20]{}; //0x0170
			boost::shared_ptr<CFont> mPrimaryFont; //0x0184
			boost::shared_ptr<CFont> mSecondaryFont; //0x018C
			boost::shared_ptr<CFont> mTertiaryFont; //0x0194
			char pad_019C[36]{}; //0x019C
			class CSpriteButton* mCloseButton = nullptr; //0x01C0
			char pad_01C4[48]{}; //0x01C4
			SMainButtonStyle mButtonStyle; //0x01F4
			char pad_024C[8]{}; //0x024C


		public:
			CPopupScreenBase() : CBloonsBaseScreen() {

			};
			CPopupScreenBase(CGameSystemPointers* pCGameSystemPointers, std::string screenName) : CBloonsBaseScreen() {
				ThisConstruct<Sigs::CPopupScreenBase_CCTOR>(this, pCGameSystemPointers, screenName);
			}

			//virtual void DrawForeground() {}
			virtual CMainButton* CreateDebugButton(std::string param_1, std::string iconSprite, std::string buttonSprite, std::string param_4, Vec2F& param_5) { return nullptr; }
			virtual CMainButton* CreateButton(std::string buttonName, std::string buttonImage, std::string iconImage, std::string buttonText, Vec2F position) { return nullptr; }
			virtual CMainButton* CreateButton(CBasePositionableObject* button, std::string buttonName, std::string buttonImage, std::string iconImage, std::string buttonText, Vec2F position) { return nullptr; }
			virtual CMainButton* CreateButtonBasic(std::string param_1, std::string param_2, std::string param_3, std::string param_4, Vec2F position) { return nullptr; }
			virtual CMainButton* CreateButtonBasic(CBasePositionableObject* button, std::string param_1, std::string param_2, std::string param_3, std::string param_4, Vec2F position) { return nullptr; }
			virtual CToggleButton* CreateButtonToggle(std::string param_1, std::string param_2, std::string param_3, std::string param_4, std::string param_5, bool param_6, Vec2F param_7, Vec2F param_8) { return nullptr; }
			virtual CToggleButton* CreateButtonToggle(CBasePositionableObject* button, std::string param_1, std::string param_2, std::string param_3, std::string param_4, std::string param_5, bool param_6, Vec2F param_7, Vec2F param_8) { return nullptr; }
			virtual void ChangeState(int eScreenSubState) {}


			void AddObject(CBasePositionableObject* object, int param_1) {
				ThisCall<Sigs::CPopupScreenBase_AddObject, &CPopupScreenBase::AddObject>(this, object, param_1);
			}
			void AddNavButton(eNavButtonType type, std::string icon) {
				ThisCall<Sigs::CPopupScreenBase_AddNavButton, &CPopupScreenBase::AddNavButton>(this, type, icon);
			}
			void* AddToPoppingList(CBasePositionableObject* object, CBasePositionableObject* parent, CBasePositionableObject* object_src, bool param_4) {
				return ThisCall<Sigs::CPopupScreenBase_AddToPoppingList, &CPopupScreenBase::AddToPoppingList>(this, object, parent, object_src, param_4);
			}
		};

		static_assert(sizeof(CPopupScreenBase) == 0x0254);
		static_assert(offsetof(CPopupScreenBase, mRoot) == 0x11C);
	} // namespace Classes

} // namespace NKHook5
