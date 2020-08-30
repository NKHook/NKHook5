#pragma once
#include "CSprite.h"

class CCompoundSprite : public CSprite
{
public:
	int CCompoundSpriteStart; //0x0104
	class CEventManager* CEventManager; //0x0108
	char pad_010C[56]; //0x010C
public:
	CCompoundSprite() : CSprite() {
		Constructor(this);
	}
	void Constructor(CCompoundSprite* self);
}; //Size: 0x0144