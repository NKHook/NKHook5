#pragma once

#include <string>

namespace NKHook5::Signatures {
	enum class Sigs {
		/* CApp */
		CApp_Init_Debugger_Patch,
		/* CApplyStatusEffectTask */
		CApplyStatusEffectTask_VTable,
		CApplyStatusEffectTask_Fire,
		/* CAssetBag */
		CAssetBag_StartUsing,
		/* CBaseButton */
		CBaseButton_VTable,
		CBaseButton_CCTOR,
		/* CBaseFactory */
		/* CBaseFileIO */
		CBaseFileIO_FileExists,
		CBaseFileIO_OpenFile,
		/* CBasePositionableObject */
		CBasePositionableObject_AssignParent,
		CBasePositionableObject_MakeDirty,
		/* CBaseScreen */
		CBaseScreen_CCTOR,
		CBaseScreen_GetScreen,
		CBaseScreen_OpenPopup,
		CBaseScreen_StartUsingAsset,
		/* CBaseTower */
		/* CBloon */
		CBloon_ApplyEffect,
		CBloon_Update,
		/* CBloonFactory */
		CBloonFactory_CCTOR,
		/* CBloonsBaseScreen */
		CBloonsBaseScreen_CCTOR,
		CBloonsBaseScreen_Init,
		/* CBloonsTD5Game */
		CBloonsTD5Game_CCTOR,
		CBloonsTD5Game_LoadAssets,
		/* CCollectableTask */
		CCollectableTask_VTable,
		CCollectableTask_Clone,
		CCollectableTask_GiveContentsAndDie,
		CCollectableTask_Update,
		/* CCompoundSprite */
		CCompoundSprite_VTable,
		CCompoundSprite_CCTOR,
		CCompoundSprite_Load,
		/* CDGSplashScreen */
		CDGSplashScreen_VTable,
		CDGSplashScreen_Init,
		CDGSplashScreen_Hide,
		/* CEffectTask */
		CEffectTask_ReadTask_Patch,
		CEffectTask_FireAt,
		/* CFile */
		CFile_ReadBytes,
		/* CFlagStringConvertor */
		CFlagStringConvertor_FlagToString,
		CFlagStringConvertor_LoadCategory,
		CFlagStringConvertor_StringToFlag,
		/* CFont */
		/* CFontManager */
		CFontManager_GetFont,
		/* CGameScreen */
		CGameScreen_Init,
		/* C_GameSFXManager */
		C_GameSFXManager_GetInstance,
		C_GameSFXManager_Play,
		/* CGameSystemPointers */
		/* CGlueStatusEffect */
		CGlueStatusEffect_VTable,
		CGlueStatusEffect_CCTOR,
		/* CLoc */
		CLoc_FindText,
		CLoc_GetText,
		/* CMainButton */
		CMainButton_CCTOR,
		/* CNapalmStatusEffect */
		CNapalmStatusEffect_VTable,
		/* Color */
		/* CPlayerProfileV1 */
		CPlayerProfileV1_InternalLoad,
		CPlayerProfileV1_Save,
		/* CPopupScreenBase */
		CPopupScreenBase_VTable,
		CPopupScreenBase_CCTOR,
		CPopupScreenBase_AddObject,
		CPopupScreenBase_AddNavButton,
		CPopupScreenBase_AddToPoppingList,
		/* CProjectile */
		CProjectile_VTable,
		CProjectile_CCTOR_A,
		CProjectile_CCTOR_B,
		CProjectile_CCTOR_C,
		CProjectile_Clone,
		CProjectile_Update,
		/* CReferenceCounted */
		/* CRenderableTextureObject */
		/* CScreenManager */
		/* CSettingsScreen */
		CSettingsScreen_VTable,
		CSettingsScreen_CCTOR,
		CSettingsScreen_Hide,
		CSettingsScreen_InitLayout,
		CSettingsScreen_Input,
		CSettingsScreen_Process,
		/* CSprite */
		CSprite_VTable,
		CSprite_CCTOR,
		CSprite_SetTexture,
		/* CStatusEffect */
		CStatusEffect_IncTowerRef,
		/* CTextObject */
		CTextObject_VTable,
		CTextObject_CCTOR_A,
		CTextObject_CCTOR_B,
		CTextObject_CCTOR_C,
		/* CTextureManager */
		CTextureManager_GetSpriteInfoPtr,
		CTextureManager_LoadCompound,
		/* CTowerFactory */
		CTowerFactory_CCTOR,
		CTowerFactory_GetTowerInfo,
		CTowerFactory_GetTowerName,
		/* CUnzippedFile */
		CUnzippedFile_CCTOR,
		/* CWeapon */
		CWeapon_Fire,
		/* CWeaponFactory */
		CWeaponFactory_CCTOR,
		CWeaponFactory_ParseTask,
		/* CWeaponTask */
		/* CXmlFontImporter */
		/* CZipFile */
		CZipFile_CCTOR,
		CZipFile_Open,
		CZipFile_LoadFrom,
		/* GLRenderLayer */
		/* IBasePointers */
		IBasePointers_CCTOR,
		/* IFontImporter */
		/* IScreenData */
		IScreenData_VTable,
		/* ITextureLoaderListener */
		/* JsonObject */
		JsonObject_ReadBoolProperty,
		JsonObject_ReadIntProperty,
		/* Matrix16F */
		/* Screens */
		Screens_GetScreenForParadigm,
		/* ScriptedScreen */
		ScriptedScreen_VTable,
		ScriptedScreen_CCTOR,
		/* ScriptedScreenData */
		ScriptedScreenData_VTable,
		/* SMainButtonStyle */
		SMainButtonStyle_CCTOR,
		SMainButtonStyle_CopyCCTOR,
		/* Unknown */
		Unknown_WinMain,
		/* Vec2F */
		/* Vec3F */
		/* ZipCpp */

		/* C/C++ Runtime stuff */
		CRT_operator_new,
		CRT_free
	};

	void* FindFirst(int count, ...);
	void FindAll();
	void* GetAddressOf(Sigs sig);
}
