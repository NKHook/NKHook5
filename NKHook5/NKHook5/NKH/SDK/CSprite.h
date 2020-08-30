#pragma once
#include "CRenderableTextureObject.h"

class CSprite : public CRenderableTextureObject
{
public:
	int CSpriteStart; //0x00C8
	char pad_00CC[56]; //0x00CC

	virtual void SetColour() {};
	virtual void SetColourf() {};
	virtual void SetColour_() {};
	virtual void SetColourChildren() {};
	virtual void SetColourf_() {};
	virtual void SetColour__() {};
	virtual void SetAlphaf_r() {};
	virtual void SetAlphaf() {};
	virtual void SetAlpha() {};
	virtual void GetCornerColour() {};
	virtual void GetCornerAlpha() {};
	virtual void GetSpriteInfoStruct() {};
	virtual void BindTexture() {};
	virtual void SetSecondaryColourMultiply() {};
	virtual void SetSecondaryColourMultiply_r() {};
public:
	CSprite() : CRenderableTextureObject() {
		Constructor(this);
	}
	void Constructor(CSprite* self);
}; //Size: 0x0104