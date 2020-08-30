#pragma once
#include "CRenderableTextureObject.h"

class CSprite : public CRenderableTextureObject 
{
public:

public:
	CSprite() : CRenderableTextureObject() {
		Constructor(this);
	}
	void Constructor(CSprite* self);
};