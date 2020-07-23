#pragma once
#include "pch.h"
#include "../NMath.h"
#include "../../Utils.h"
#include "CBaseTower.h"
#include "CTowerFactory.h"


void* CTowerFactory_UpdateSpriteGraphic_Addr = 0;
void CTowerFactory::UpdateSpriteGraphic(CBaseTower* tower, class STowerInfo* towerInfo) {
	if(CTowerFactory_UpdateSpriteGraphic_Addr == 0)
		CTowerFactory_UpdateSpriteGraphic_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8b ec 6a ff 68 D4 ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 6C A1 34 B0 52");
	void(__thiscall * CTowerFactory_UpdateSpriteGraphic_Func)(void*, void*);
	memcpy(&CTowerFactory_UpdateSpriteGraphic_Func, CTowerFactory_UpdateSpriteGraphic_Addr, 4);
	CTowerFactory_UpdateSpriteGraphic_Func(tower, towerInfo);
}