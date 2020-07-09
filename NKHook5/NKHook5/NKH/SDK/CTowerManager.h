#pragma once
class CTowerManager
{
public:
	class CBaseTower* (*Towers)[99999]; //0x0004
	class CBaseTower** LastTower; //0x0008

	virtual void Destructor();
}; //Size: 0x000C