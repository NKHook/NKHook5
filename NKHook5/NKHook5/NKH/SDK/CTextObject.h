#pragma once
#include <string>
#include "CBasePositionableObject.h"

using namespace std;
class CTextObject : public CBasePositionableObject
{
public:
	char pad_0000[8];
	char Text[16]; //0x00C8
	int32_t TextLength; //0x00D8
	char pad_00DC[308]; //0x00DC

	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void SetTexture();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void SetText(basic_string<char>* text);
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();

public:
	CTextObject(string text) {

	}
}; //Size: 0x0210