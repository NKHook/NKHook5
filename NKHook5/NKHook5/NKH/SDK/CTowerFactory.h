#pragma once
#include "CFlagStringConvertor.h"

class CTowerFactory
{
public:
	char pad_0000[80]; //0x0000
	class CFlagStringConvertor CFlagStringConvertor; //0x0050
	char pad_00B0[176]; //0x00B0

public:
	void UpdateSpriteGraphic(CBaseTower* tower, class STowerInfo* towerInfo);
}; //Size: 0x0160