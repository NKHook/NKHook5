#pragma once

#include "CTextureLoader.h"
#include "SSpriteInfo.h"

#include "Macro.h"
#include "../Signatures/Signature.h"

#include <string>

namespace NKHook5 {
	namespace Classes {
		using namespace Signatures;

		class CTextureManager {
		public:
			CTextureLoader* pTexLoader; //0x0000
			char pad_0004[188]; //0x0004
		public:
			SSpriteInfo* GetSpriteInfoPtr(std::string spritesheetName, std::string spriteName) {
				return ThisCall<SSpriteInfo*, CTextureManager*, std::string&, std::string&>(Sigs::CTextureManager_GetSpriteInfoPtr, this, spritesheetName, spriteName);
			}
		};
	}
}