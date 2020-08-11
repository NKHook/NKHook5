#pragma once
#include "pch.h"
#include "../NMath.h"
#include "../../Utils.h"
#include "CBaseTower.h"
#include "CTowerFactory.h"
#include "CBasePositionableObject.h"
#include "CRenderableTextureObject.h"
#include "CTextObject.h"
#include "IBasePointers.h"
#include "CBaseScreen.h"

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
void CBasePositionableObject::Constructor(CBasePositionableObject* self) {
	if (CBasePositionableObject_Constructor_Addr == 0) {
		CBasePositionableObject_Constructor_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 57 8b f9 0f 57 c0 8d");
		if (CBasePositionableObject_Constructor_Addr == 0) {
			cout << "CRITICAL ERROR: COULDN'T CONSTRUCT A CBPO!" << endl;
		}
	}
	void (__thiscall * CBasePositionableObject_Constructor_Func)(void*);
	memcpy(&CBasePositionableObject_Constructor_Func, &CBasePositionableObject_Constructor_Addr, 4);
	CBasePositionableObject_Constructor_Func(self);
}
#pragma endregion
#pragma region CRenderableTextureObject_Constructor
void* CRenderableTextureObject_Constructor_Addr = 0;
void CRenderableTextureObject::Constructor(CRenderableTextureObject* self) {
	if (CRenderableTextureObject_Constructor_Addr == 0) {
		CRenderableTextureObject_Constructor_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "56 8b f1 e8 ?? ?? ?? ?? a0");
		if (CRenderableTextureObject_Constructor_Addr == 0) {
			cout << "CRITICAL ERROR: COULDN'T CONSTRUCT A CRTO!" << endl;
		}
	}
	void (__thiscall * CRenderableTextureObject_Constructor_Func)(void*);
	memcpy(&CRenderableTextureObject_Constructor_Func, &CRenderableTextureObject_Constructor_Addr, 4);
	CRenderableTextureObject_Constructor_Func(self);
}
#pragma endregion
#pragma region CTextObject_Constructor
void* CTextObject_Constructor_Addr = 0;
void CTextObject::Constructor(CTextObject* self, Vector2* position, CFont** font, string* text) {
	if (CTextObject_Constructor_Addr == 0) {
		CTextObject_Constructor_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 00 00 00 00 50 83 ec 30 a1 ?? ?? ?? ?? 33 c5 89 45 ec 53 56 57 50 8d 45 f4 64 a3 00 00 00 00 8b f1 89 75 d0");
		if (CTextObject_Constructor_Addr == 0) {
			cout << "CRITICAL ERROR: COULDN'T CONSTRUCT A CTO!" << endl;
		}
	}
	void (__thiscall * CTextObject_Constructor_Func)(void*, void*, void*, void*);
	memcpy(&CTextObject_Constructor_Func, &CTextObject_Constructor_Addr, 4);
	CTextObject_Constructor_Func(self, position, font, text);
}
#pragma endregion
#pragma region IBasePointers_Constructor
void* IBasePointers_Constructor_Addr = 0;
void IBasePointers::Constructor(IBasePointers* self) {
	if (IBasePointers_Constructor_Addr == 0) {
		IBasePointers_Constructor_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "c7 01 00 00 00 00 8b c1 c7 41 04 00 00 00 00 c7 41 08 00 00 00 00 c7 41 0c 00 00 00 00 c7 41 10 00 00 00 00 c7 41 14 00 00 00 00 c7 41 18 00 00 00 00 c7 41 1c 00 00 00 00 c7 41 20 00 00 00 00 c7 41 24 00 00 00 00 c7 41 28 00 00 00 00 c7 41 2c 00 00 00 00 c7 41 30 00 00 00 00 c7 41 34 00 00 00 00 c7 41 38 00 00 00 00 c7 41 3c 00 00 00 00 c7"); //c7 01 00 00 00 00 8b c1 c7 41 04 00 00 00 00 c7 41 08 00 00 00 00 c7 41 0c 00 00 00 00 c7 41 10 00 00 00 00 c7 41 14 00 00 00 00 c7 41 18 00 00 00 00 c7 41 1c 00 00 00 00 c7 41 20 00 00 00 00 c7 41 24 00 00 00 00 c7 41 28 00 00 00 00 c7 41 2c 00 00 00 00 c7 41 30 00 00 00 00 c7 41 34 00 00 00 00 c7 41 38 00 00 00 00 c7 41 3c 00 00 00 00 c7
		if (IBasePointers_Constructor_Addr == 0) {
			cout << "CRITICAL ERROR: COULDN'T CONSTRUCT A IBP!" << endl;
		}
	}
	void(__thiscall * IBasePointers_Constructor_Func)(void*);
	memcpy(&IBasePointers_Constructor_Func, &IBasePointers_Constructor_Addr, 4);
	IBasePointers_Constructor_Func(self);
}
#pragma endregion
#pragma region CBaseScreen_Constructor
void* CBaseScreen_Constructor_Addr = 0;
void CBaseScreen::Constructor(CBaseScreen* self, string* screenName) {
	if (CBaseScreen_Constructor_Addr == 0) {
		CBaseScreen_Constructor_Addr = (void*)Utils::findPattern(Utils::getModuleBase(), Utils::getBaseModuleEnd(), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 00 00 00 00 50 83 ec 08 56 57 a1 ?? ?? ?? ?? 33 c5 50 8d 45 f4 64 a3 00 00 00 00 8b f9 89 7d f0 8d 4f"); //55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 00 00 00 00 50 83 ec 08 56 57 a1 ?? ?? ?? ?? 33 c5 50 8d 45 f4 64 a3 00 00 00 00 8b f9 89 7d f0 8d 4f
		if (CBaseScreen_Constructor_Addr == 0) {
			cout << "CRITICAL ERROR: COULDN'T CONSTRUCT A CBS!" << endl;
		}
	}
	void(__thiscall * CBaseScreen_Constructor_Func)(void*, void*);
	memcpy(&CBaseScreen_Constructor_Func, &CBaseScreen_Constructor_Addr, 4);
	CBaseScreen_Constructor_Func(self, screenName);
}
#pragma endregion





