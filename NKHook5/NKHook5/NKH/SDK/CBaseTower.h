#pragma once
#include "Color.h"
#include "CBasePositionableObject.h"

class CBaseTower : public CBasePositionableObject
{
public:
	int TowerStart; //0x00A8
	char pad_00AC[36]; //0x00AC
	int64_t TypeFlag; //0x00D0
	char pad_00D8[24]; //0x00D8
	bool Selected; //0x00F0
	bool Sellable; //0x00F1
	char pad_00F2[1]; //0x00F2
	bool Upgradable; //0x00F3
	char pad_00F4[16]; //0x00F4
	class CCompoundSprite* CCompoundSprite; //0x0104
	Color Color; //0x0108
	char pad_010C[44]; //0x010C
	int LeftUpgrade; //0x0138
	int RightUpgrade; //0x013C
	char pad_0140[4]; //0x0140
	int SellPrice; //0x0144
	char pad_0148[56]; //0x0148
	int64_t TargetModeFlag; //0x0180
	char pad_0188[140]; //0x0188
	bool N000002DB; //0x0214
	bool Hovered; //0x0215
	char pad_0216[175]; //0x0216

public:
	Vector2& getPosition() {
		Vector2 toRet = Vector2(this->PosX, this->PosY);
		return toRet;
	}
	long long& getTypeFlag() {
		return this->TypeFlag;
	}
	void setTypeFlag(long& type) {
		this->TypeFlag = type;
	}
	bool& isSelected() {
		return this->Selected;
	}
	class CCompoundSprite& getCCompoundSprite() {
		return *this->CCompoundSprite;
	}
	bool& isHovered() {
		return this->Hovered;
	}
	void incrementUpgradeLevel(int path);
}; //Size: 0x0184