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
	CSprite(Vector2* position, void* sSpriteInfo, bool param_3) : CRenderableTextureObject() {
		cout << "pre sprite" << endl;
		Constructor(this, position, sSpriteInfo, param_3);
		cout << "post sprite" << endl;
	}
	void Constructor(CSprite* self, Vector2* position, void* sSpriteInfo, bool param_3);
}; //Size: 0x0104