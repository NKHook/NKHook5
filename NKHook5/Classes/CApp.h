#pragma once

#include "CAssetBag.h"
#include "CFont.h"
#include "CGameSystemPointers.h"
#include "IBasePointers.h"

#include <boost/shared_ptr.hpp>

#include <string>

namespace NKHook5::Classes {

	//Somehow the render layer pointer is only in CApp, and before the IBasePointers class
	struct RenderLayerWeirdness
	{
		void* mRenderLayer = nullptr;
	};

	class CApp : public RenderLayerWeirdness, public IBasePointers {
	public:
		char pad_0074[52]; //0x0074
		std::string mVersionNumber; //0x00A8
		char pad_00C0[52]; //0x00C0
		bool mHasBundles; //0x00F4
		char pad_00F5[79]; //0x00F5
		boost::shared_ptr<CAssetBag> mAssetBag; //0x0144
		CGameSystemPointers* mGameSystemPointers = nullptr; //0x014C
		char pad_0150[4]; //0x0150
		boost::shared_ptr<CFont> mFont; //0x0154
		char pad_015C[24]; //0x015C
		float mSecondTimer; //0x0174
		int32_t mMillis; //0x0178
		char pad_017C[8]; //0x017C
		std::string mLocale; //0x0184
		char pad_019C[20]; //0x019C


	public:
		virtual ~CApp() = default;
	};

	static_assert(sizeof(CApp) == 0x1B0);
	static_assert(offsetof(CApp, mVersionNumber) == 0xA8);
	static_assert(offsetof(CApp, mLocale) == 0x184);
}