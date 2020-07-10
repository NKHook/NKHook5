#pragma once
#include "../NMath.h"
class CBloon
{
public:
	char pad_0000[160]; //0x0000
	Vector2 SpriteSize; //0x00A0
	char pad_00A8[32]; //0x00A8
}; //Size: 0x00C8