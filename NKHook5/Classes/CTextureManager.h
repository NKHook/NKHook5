#pragma once

#include "CTextureLoader.h"
#include "SSpriteInfo.h"

#include "Macro.h"
#include "../Signatures/Signature.h"

#include <string>

namespace NKHook5::Classes {
	using namespace Signatures;

	class CTextureManager {
	public:
		CTextureLoader* pTexLoader; //0x0000
		char pad_0004[188]; //0x0004
	public:
		SSpriteInfo* GetSpriteInfoPtr(const std::string& spritesheetName, const std::string& spriteName) {
			return ThisCall<Sigs::CTextureManager_GetSpriteInfoPtr>(&CTextureManager::GetSpriteInfoPtr, this, spritesheetName, spriteName);
		}
	};
}