#pragma once
#include <string>
#include "CRenderableTextureObject.h"
#include "CFont.h"
#include "CTexture.h"

using namespace std;
class CTextObject : public CRenderableTextureObject
{
public:
	string text;
	//char Text[16]; //0x00C8
	//int TextLength; //0x00D8
	//int fifteenI; //0x00DC
	class CFont* Font; //0x00E0
	char pad_00E4[24]; //0x00E4
	float pointZeroFour; //0x00FC
	char pad_0100[8]; //0x0100
	float onef_2; //0x0108
	float onef_3; //0x010C
	int zerozerozeroeighty; //0x0110
	float onef_4; //0x0114
	float onef_5; //0x0118
	float onef_6; //0x011C
	float onef_7; //0x0120
	char pad_0124[8]; //0x0124
	int eightI; //0x012C
	char pad_0130[4]; //0x0130
	int zerozerozeroone; //0x0134
	int onei; //0x0138
	char pad_013C[64]; //0x013C


	virtual void Function44() {};
	virtual void Function45() {};
	virtual void Function46() {};
	virtual void Function47() {};
	virtual void Function48() {};
	virtual void Function49() {};
	virtual void Function50() {};
	virtual void SetTexture(CTexture* texture) {};
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
	CTextObject(Vector2* position, string* text) : CRenderableTextureObject() {
		//this->Texture = Utils::getFontTexture();
		Constructor(this, position, &Utils::getGame()->CFont, text);
	}
	void Constructor(CTextObject* self, Vector2* position, CFont** font, string* text);
	//You have to set the text *after* construction
	//CTextObject(string text) : CRenderableTextureObject() {
	//	int vTableAddr = Utils::getModuleBase() + 0x727508; // "BTD5-Win.exe"+727508 
	//	memcpy(this, &vTableAddr, 4);

	//	this->Texture = Utils::getFontTexture();
	//	this->text = text;
	//	this->Font = Utils::getGame()->CFont;
	//	this->zerozerozeroone = 0x1000000;
	//	this->onei = 1;
	//	this->pointZeroFour = .04f;
	//	this->pointZeroFour = .04f;
	//	this->onef_2 = 1.0f;
	//	this->onef_3 = 1.0f;
	//	this->zerozerozeroeighty = 0x80000000;
	//	this->onef_4 = 1.0f;
	//	this->onef_5 = 1.0f;
	//	this->onef_6 = 1.0f;
	//	this->onef_7 = 1.0f;
	//	this->eightI = 8;
	//}
}; //Size: 0x0210