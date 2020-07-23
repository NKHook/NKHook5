#pragma once
#include "pch.h"
#include "../NMath.h"
#include "../../Utils.h"
#include "CBaseTower.h"
#include "CTowerFactory.h"

using namespace std;


void* CTowerFactory_UpdateSpriteGraphic_Addr = 0;
void CTowerFactory::UpdateSpriteGraphic(CBaseTower* tower, class STowerInfo* towerInfo) {
	if(CTowerFactory_UpdateSpriteGraphic_Addr == 0)
		CTowerFactory_UpdateSpriteGraphic_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8b ec 6a ff 68 D4 ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 6C A1 34 B0 52");
	void(__thiscall * CTowerFactory_UpdateSpriteGraphic_Func)(void*, void*);
	memcpy(&CTowerFactory_UpdateSpriteGraphic_Func, CTowerFactory_UpdateSpriteGraphic_Addr, 4);
	CTowerFactory_UpdateSpriteGraphic_Func(tower, towerInfo);
}

void* CBaseTower_IncrementUpgradeLevel_Addr = 0;
void CBaseTower::incrementUpgradeLevel(int path) {
	if(CBaseTower_IncrementUpgradeLevel_Addr == 0)
		CBaseTower_IncrementUpgradeLevel_Addr = (void*)(Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "51 53 56 57 8B 7D 08 8B F1 8D 04")-6);
	if (CBaseTower_IncrementUpgradeLevel_Addr != 0) {
		cout << "Func found" << endl;
		void(__thiscall* CBaseTower_IncrementUpgradeLevel_Func)(CBaseTower*, int)=0;
		cout << "Created void func shit" << endl;
		memcpy(&CBaseTower_IncrementUpgradeLevel_Func, &CBaseTower_IncrementUpgradeLevel_Addr, 4);
		cout << hex << "CBaseTower_IncrementUpgradeLevel_Func: " << CBaseTower_IncrementUpgradeLevel_Func << endl;
		CBaseTower_IncrementUpgradeLevel_Func(this, path);
	}
	else {
		cout << "Function not found!" << endl;
	}
}