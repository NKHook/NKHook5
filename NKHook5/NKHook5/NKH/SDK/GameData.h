#pragma once
#include <string>
using namespace std;
class GameData
{
public:
	char pad_0000[88]; //0x0000
	string CurrentMap; //0x0058
	char pad_0070[24]; //0x0070
	int Health; //0x0088
	char pad_008C[4]; //0x008C
	double Cash; //0x0090
	char pad_0098[176]; //0x0098
	char SteamName[24]; //0x0148

public:
	string& getCurrentMap() {
		return this->CurrentMap;
	}
	int& getHealth() {
		return this->Health;
	}
	double& getCash() {
		return this->Cash;
	}
	void setHealth(int value) {
		this->Health = value;
	}
	void setCash(double value) {
		this->Cash = value;
	}
}; //Size: 0x0160