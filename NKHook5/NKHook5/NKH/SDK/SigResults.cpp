#pragma once
#include "pch.h"
#include "../NMath.h"
#include "../../Utils.h"
#include "CBaseTower.h"
#include "CTowerFactory.h"
#include "CBasePositionableObject.h"

using namespace std;

#pragma region CTowerFactory_UpdateSpriteGraphic
void* CTowerFactory_UpdateSpriteGraphic_Addr = 0;
void CTowerFactory::UpdateSpriteGraphic(CBaseTower* tower, class STowerInfo* towerInfo) {
	if (CTowerFactory_UpdateSpriteGraphic_Addr == 0)
		CTowerFactory_UpdateSpriteGraphic_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8b ec 6a ff 68 D4 ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 6C A1 34 B0 52");
	void(__thiscall * CTowerFactory_UpdateSpriteGraphic_Func)(void*, void*);
	memcpy(&CTowerFactory_UpdateSpriteGraphic_Func, &CTowerFactory_UpdateSpriteGraphic_Addr, 4);
	CTowerFactory_UpdateSpriteGraphic_Func(tower, towerInfo);
}
#pragma endregion
#pragma region CBaseTower_IncrementUpgradeLevel
void* CBaseTower_IncrementUpgradeLevel_Addr = 0;
void CBaseTower::incrementUpgradeLevel(int path) {
	if (CBaseTower_IncrementUpgradeLevel_Addr == 0)
		CBaseTower_IncrementUpgradeLevel_Addr = (void*)(Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "51 53 56 57 8B 7D 08 8B F1 8D 04") - 6);
	if (CBaseTower_IncrementUpgradeLevel_Addr != 0) {
		cout << "Func found" << endl;
		void(__thiscall * CBaseTower_IncrementUpgradeLevel_Func)(CBaseTower*, int) = 0;
		cout << "Created void func shit" << endl;
		memcpy(&CBaseTower_IncrementUpgradeLevel_Func, &CBaseTower_IncrementUpgradeLevel_Addr, 4);
		cout << hex << "CBaseTower_IncrementUpgradeLevel_Func: " << CBaseTower_IncrementUpgradeLevel_Func << endl;
		CBaseTower_IncrementUpgradeLevel_Func(this, path);
	}
	else {
		cout << "Function not found!" << endl;
	}
}
#pragma endregion
#pragma region CBasePositionableObject_Constructor
void* CBasePositionableObject_Constructor_Addr = 0;
CBasePositionableObject* CBasePositionableObject::Constructor(CBasePositionableObject* self) {
	if (CBasePositionableObject_Constructor_Addr == 0) {
		CBasePositionableObject_Constructor_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 8b f9 0f 57 c0 8d");
		if (CBasePositionableObject_Constructor_Addr == 0) {
			cout << "CRITICAL ERROR: COULDN'T CONSTRUCT A CBPO!" << endl;
		}
	}
	CBasePositionableObject* (__thiscall * CBasePositionableObject_Constructor_Func)(void*);
	memcpy(&CBasePositionableObject_Constructor_Func, &CBasePositionableObject_Constructor_Addr, 4);
	return CBasePositionableObject_Constructor_Func(self);
}
#pragma endregion





