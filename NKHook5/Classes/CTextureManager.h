#pragma once

#include "../../Util/NewFramework.h"

#include "CTextureLoader.h"
#include "SCompoundSprite.h"
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
		SSpriteInfo* GetSpriteInfoPtr(const nfw::string& spritesheetName, const nfw::string& spriteName) {
			return ThisCall<Sigs::CTextureManager_GetSpriteInfoPtr, &CTextureManager::GetSpriteInfoPtr>(this, spritesheetName, spriteName);
		}
		SCompoundSprite* LoadCompound(const nfw::string& directory, const nfw::string& graphicName, bool unk = true)
		{
			return ThisCall<Sigs::CTextureManager_LoadCompound, &CTextureManager::LoadCompound>(this, directory, graphicName, unk);
		}
	};
}