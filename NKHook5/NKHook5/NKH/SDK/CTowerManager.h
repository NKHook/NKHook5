#pragma once
class CTowerManager
{
public:
	class CBaseTower** Towers; //0x0004
	class CBaseTower** LastTower; //0x0008

	virtual void Destructor();

public:
	class CBaseTower& getTower(int i) {
		return *this->Towers[i];
	}
	class CBaseTower& getLastTower() {
		return **this->LastTower;
	}
	int getTowerCount() {
		int i = 0;
		if (Towers == nullptr) {
			return i;
		}
		if (*Towers == nullptr) {
			return i;
		}
		return ((size_t)(LastTower) - (size_t)(Towers)) / sizeof(CBaseTower**);
	}
	typedef std::function<void(CBaseTower&)> towerLoopFunc;
	void forEachTower(const towerLoopFunc& theFunc) {
		for (int i = 0; i < getTowerCount(); i++) {
			const towerLoopFunc func = theFunc;
			func(*Towers[i]);
		}
	}
}; //Size: 0x000C