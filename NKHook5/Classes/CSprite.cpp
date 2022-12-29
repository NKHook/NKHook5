#include "CSprite.h"

using namespace NKHook5;
using namespace NKHook5::Classes;

void CSprite::SetTexture(SSpriteInfo* info, bool unk)
{
	ThisCall<void, CSprite*, SSpriteInfo*, bool>(Sigs::CSprite_SetTexture, this, info, unk);
}