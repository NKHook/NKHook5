#include "CSprite.h"

#include "Macro.h"

using namespace NKHook5;
using namespace NKHook5::Classes;

CSprite::CSprite(SSpriteInfo* spriteInfo, bool param_2, Vec2F location, bool vanillaVft)
{
	ThisCall<CSprite*, CSprite*, SSpriteInfo*, bool, Vec2F>(Sigs::CSprite_CCTOR, this, spriteInfo, param_2, location);
	if (vanillaVft)
	{
		*(void**)this = Signatures::GetAddressOf(Sigs::CSprite_VTable);
	}
}

void CSprite::SetTexture(SSpriteInfo* info, bool unk)
{
	ThisCall<void, CSprite*, SSpriteInfo*, bool>(Sigs::CSprite_SetTexture, this, info, unk);
}