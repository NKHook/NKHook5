#pragma once

class CBaseTower
{
public:
	char pad_0000[144]; //0x0000
	Vector2 Position; //0x0090
	char pad_0098[56]; //0x0098
	int64_t TypeFlag; //0x00D0
	char pad_00D8[24]; //0x00D8
	bool Selected; //0x00F0
	char pad_00F1[19]; //0x00F1
	class CCompoundSprite* CCompoundSprite; //0x0104
	char pad_0108[268]; //0x0108
	bool N000002DB; //0x0214
	bool Hovered; //0x0215
	char pad_0216[174]; //0x0216

public:
	Vector2& getPosition() {
		return this->Position;
	}
	long long& getTypeFlag() {
		return this->TypeFlag;
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
	void IncrementUpgradeLevel(int path);
}; //Size: 0x0184