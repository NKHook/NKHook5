#pragma once
#include "IBasePointers.h"
// Created with ReClass.NET 1.2 by KN4CK3R

class CBaseScreen : public IBasePointers
{
public:
	int BaseScreenStart; //0x0070
	char pad_0074[8]; //0x0074
	class CBaseScreen** Children; //0x007C
	class CBaseScreen** lastChild; //0x0080
	char pad_0084[4]; //0x0084
	string screenName;
	char pad_00A0[4]; //0x00A0
	class CBaseScreen* Parent; //0x00A4
	char pad_00A8[424]; //0x00A8

	virtual void Function0() {};
	virtual void Function1() {};
	virtual void Init() {};
	virtual void Function3() {};
	virtual void Function4() {};
	virtual void Function5() {};
	virtual void Function6() {};
	virtual void Function7() {};
	virtual void Function8() {};
	virtual void Function9() {};
	virtual void Function10() {};
	virtual void Function11() {};
	virtual void Function12() {};
	virtual void Function13() {};
	virtual void Function14() {};
	virtual void Function15() {};
	virtual void Function16() {};
	virtual void Function17() {};
	virtual void Draw() {};
	virtual void Function19() {};
	virtual void Function20() {};
	virtual void SetupPointers(CBaseScreen*) {};
	virtual void Function22() {};
	virtual void Function23() {};

public:
	CBaseScreen(string* screenName) {
		Constructor(this, screenName);
	}
	void Constructor(CBaseScreen* self, string* screenName);
}; //Size: 0x0250