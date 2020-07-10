#pragma once
#include "../NMath.h"
class CBloon
{
public:
	char pad_0000[160]; //0x0000
	Vector2 SpriteSize; //0x00A0
	char pad_00A8[340]; //0x00A8
	class BloonData* BloonData; //0x01FC
	char pad_0200[8]; //0x0200

public:
	Vector2& getSpriteSize() {
		return this->SpriteSize;
	}
	class BloonData& getBloonData() {
		return *this->BloonData;
	}
}; //Size: 0x00C8