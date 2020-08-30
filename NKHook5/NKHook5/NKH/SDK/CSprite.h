#pragma once
#include "CRenderableTextureObject.h"

class CSprite : public CRenderableTextureObject 
{
public:
	int CSpriteStart; //0x00C8
	char pad_00CC[56]; //0x00CC
public:
	CSprite() : CRenderableTextureObject() {
		Constructor(this);
	}
	void Constructor(CSprite* self);
}; //Size: 0x0104