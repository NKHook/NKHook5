#pragma once

#include "../Util/NewFramework.h"
#include "ITextureLoaderListener.h"

namespace NKHook5::Classes {
	class CAssetBag : public ITextureLoaderListener
	{
	public:
		enum class eAssetType : uint32_t {
			TEXTURE = 0,
			FONT = 1
		};

		char pad_0004[4]; //0x0004
		class CTextureLoader* pCTextureLoader; //0x0008
		char pad_000C[28]; //0x000C
		nfw::string owner; //0x0028
		char pad_0040[40]; //0x0040
	public:
		virtual ~CAssetBag() {};

		void StartUsing(const eAssetType& type, const nfw::string& asset);
	}; //Size: 0x0068
}
