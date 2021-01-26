#pragma once
#include "CSprite.h"

class CCompoundSprite : public CSprite
{
public:
	int CCompoundSpriteStart; //0x0104
	class CEventManager* CEventManager; //0x0108
	char pad_010C[60]; //0x010C

	virtual void GetTextureName() {};
public:
	CCompoundSprite(Vector2* position, void* sCompoundSpriteInfo, void* cEventManager) : CSprite(position, sCompoundSpriteInfo, false) {
		cout << "pre compound sprite" << endl;
		Constructor(this, position, sCompoundSpriteInfo, cEventManager);
		cout << "post compound sprite" << endl;
	}
	void Constructor(CCompoundSprite* self, Vector2* position, void* sCompoundSpriteInfo, void* cEventManager);
}; //Size: 0x0148