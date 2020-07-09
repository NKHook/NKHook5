#pragma once
#include "../NMath.h"
class WinInput
{
public:
	char pad_0000[12]; //0x0000
	int32_t ClickState; //0x000C
	Vector2 ClickStartPos; //0x0010
	Vector2 ClickedMousePos; //0x0018
	Vector2 MousePos; //0x0020
	char pad_0028[4]; //0x0028

	Vector2 getMousePos() {
		return this->MousePos;
	}
}; //Size: 0x002C