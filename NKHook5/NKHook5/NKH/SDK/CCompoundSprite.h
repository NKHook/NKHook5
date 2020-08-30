#pragma once
#include "CSprite.h"

class CCompoundSprite : public CSprite
{
public:
	char pad_0000[4]; //0x0000

public:
	CCompoundSprite() : CSprite() {
		Constructor(this);
	}
	void Constructor(CCompoundSprite* self);
}; //Size: 0x0004