#pragma once

#include "../Util/NewFramework.h"
#include "../Utils.h"

#include "CAssetBag.h"
#include "IBasePointers.h"
#include "IScreenData.h"
#include "SGameTime.h"
#include "Macro.h"

#include <boost/shared_ptr.hpp>

#include <cstdint>
#include <list>
#include <string>
#include <sstream>
#include <utility>
#include <vector>


namespace NKHook5::Classes
{
	using namespace Signatures;

	enum class eScreenState : int32_t {
		UNINITIALIZED,
		INITIALIZED,
		SHOWN,
		UNKNOWN_3,
		HIDDEN,
		DESTROYING,
		DESTROYED
	};
	static_assert(sizeof(eScreenState) == 0x4);

	class CBaseScreen : public IBasePointers
	{
	public:
		class N00002022* animations = nullptr; //0x0070
		char pad_0074[4]; //0x0074
		std::vector<CBaseScreen*> children; //0x0078
		char pad_0084[4]; //0x0084
		std::string mScreenName; //0x0088
		class CBaseScreen* mParentScreen = nullptr; //0x00A0
		eScreenState screenState; //0x00A4
		char pad_00A8[8]; //0x00A8
		boost::shared_ptr<CAssetBag> mAssetBag; //0x00B0


	public:
		CBaseScreen() {}
		CBaseScreen(nfw::string screenName) {
			ThisConstruct<Sigs::CBaseScreen_CCTOR>(this, std::move(screenName));
		};
		void OpenPopup(class CPopupScreenBase* popupScreen, IScreenData* popupData, const uint32_t* param_3);
		void _OpenPopup(class CPopupScreenBase* popupScreen, IScreenData* popupData);
		void StartUsingAsset(const CAssetBag::eAssetType& type, const nfw::string& assetName);
		CBaseScreen* GetScreen(const nfw::string &screenName);

		virtual ~CBaseScreen() = default;
		virtual void _PreloadAssets() {};
		virtual void Init(IScreenData* screenData) {};
		virtual void Uninit() {};
		virtual void Show() {};
		virtual void Hide() {};
		virtual void ApplicationWillResignActive() {};
		virtual void ApplicationWillTerminate() {};
		virtual void ApplicationDidBecomeActive() {};
		virtual void SelectButtonPressed() {};
		virtual void BackButtonPressed() {};
		virtual void ScreenResized() {};
		virtual nfw::string ChildScreenClosed(nfw::string screenName, bool param_2) { return screenName; };
		virtual void BatteryLevelDidChange() {};
		virtual void ProcessInit() {};
		virtual void ProcessUninit() {};
		virtual void Process() {};
		virtual void Input(SGameTime* pGameTime) {};
		virtual void Draw() {};
		virtual void DrawOverlay() {};
		virtual bool AllAssetsLoaded() { return false; };
		virtual void SetupPointers(CBaseScreen* child) {};
		virtual void RemoveScreen(CBaseScreen* child) {};
		virtual void PrintTree(int param_1, std::stringstream outstream) {};
	};

	static_assert(sizeof(CBaseScreen) == 0x00B8);
} // namespace NKHook5::Classes