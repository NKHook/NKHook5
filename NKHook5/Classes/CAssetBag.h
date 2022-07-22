#pragma once

#include <ghstl/string>
#include "ITextureLoaderListener.h"

namespace NKHook5 {
	namespace Classes {
		class CAssetBag : public ITextureLoaderListener
		{
		public:
			char pad_0004[4]; //0x0004
			class CTextureLoader* pCTextureLoader; //0x0008
			char pad_000C[28]; //0x000C
			ghstl::string owner; //0x0028
			char pad_0040[40]; //0x0040
		public:
			virtual ~CAssetBag() {};
		}; //Size: 0x0068
	}
}