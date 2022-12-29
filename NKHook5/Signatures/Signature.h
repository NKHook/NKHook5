#pragma once

#include <string>
#include <magic_enum.hpp>

namespace NKHook5 {
	namespace Signatures {
		enum class Sigs {
			/* CApp */
			/* CApplyStatusEffectTask */
			CApplyStatusEffectTask_VTable,
			CApplyStatusEffectTask_Fire,
			/* CAssetBag */
			/* CBaseButton */
			CBaseButton_VTable,
			CBaseButton_CCTOR,
			/* CBaseFactory */
			/* CBaseFileIO */
			CBaseFileIO_FileExists,
			CBaseFileIO_OpenFile,
			/* CBasePositionableObject */
			CBasePositionableObject_AssignParent,
			CBasePositionableObject_SetComplete,
			/* CBaseScreen */
			CBaseScreen_CCTOR,
			CBaseScreen_GetScreen,
			CBaseScreen_OpenPopup,
			CBaseScreen_StartUsingAsset,
			/* CBaseTower */
			/* CBloon */
			CBloon_Update,
			/* CBloonFactory */
			CBloonFactory_CCTOR,
			/* CBloonsBaseScreen */
			CBloonsBaseScreen_CCTOR,
			/* CBloonsTD5Game */
			CBloonsTD5Game_CCTOR,
			CBloonsTD5Game_LoadAssets,
			/* CCollectableTask */
			CCollectableTask_Clone,
			CCollectableTask_GiveContentsAndDie,
			CCollectableTask_Update,
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
			/* CGameSystemPointers */
			/* CLoc */
			CLoc_FindText,
			CLoc_GetText,
			/* CMainButton */
			CMainButton_CCTOR,
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
			/* CTextObject */
			CTextObject_VTable,
			CTextObject_CCTOR_A,
			CTextObject_CCTOR_B,
			CTextObject_CCTOR_C,
			/* CTextureManager */
			CTextureManager_GetSpriteInfoPtr,
			/* CTowerFactory */
			CTowerFactory_CCTOR,
			/* CUnzippedFile */
			CUnzippedFile_CCTOR,
			/* CWeapon */
			CWeapon_Fire,
			/* CWeaponFactory */
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
			CRT_free,

			SIGNATURE_COUNT
		};

		void* FindFirst(int count, ...);
		void FindAll();
		void* GetAddressOf(Sigs sig);
	}
}