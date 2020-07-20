#pragma once
#include <string>
#include "CBasePositionableObject.h"

using namespace std;
class CTextObject : public CBasePositionableObject
{
public:
	int TextObjStart; //0x00A8
	char pad_00AC[20]; //0x00AC
	class CTexture* FontTexture; //0x00C0
	char pad_00C4[4]; //0x00C4
	char Text[16]; //0x00C8
	int TextLength; //0x00D8
	int FifteenI; //0x00DC //chars until it should be a pointer
	class CFont* Font; //0x00E0

	virtual void Function44() {};
	virtual void Function45() {};
	virtual void Function46() {};
	virtual void Function47() {};
	virtual void Function48() {};
	virtual void Function49() {};
	virtual void Function50() {};
	virtual void SetTexture() {};
	virtual void Function52() {};
	virtual void Function53() {};
	virtual void Function54() {};
	virtual void Function55() {};
	virtual void Function56() {};
	virtual void SetText(basic_string<char>* text) {};
	virtual void Function58() {};
	virtual void Function59() {};
	virtual void Function60() {};

public:
	//You have to set the text *after* construction
	CTextObject() : CBasePositionableObject() {
		int vTableAddr = Utils::getModuleBase() + 0x727508; // "BTD5-Win.exe"+727508 
		memcpy(this, &vTableAddr, 4);

		this->Font = Utils::getGame()->CFont;
	}
}; //Size: 0x0210