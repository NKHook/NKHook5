#pragma once
#include <string>
using namespace std;
class BloonData
{
public:
	char* ChildBloonFileName; //0x0000
	char pad_0004[12]; //0x0004
	char TypeName[12]; //0x0010
	char pad_001C[12]; //0x001C
	int Type; //0x0028
	int Damage; //0x002C
	char pad_0030[20]; //0x0030

public:
	string& getChildBloonFileName() {
		string str = string(ChildBloonFileName);
		return str;
	}
	string& getTypeName() {
		string str = string(TypeName);
		return str;
	}
	int& getType() {
		return Type;
	}
	int& getDamage() {
		return Damage;
	}
}; //Size: 0x0044