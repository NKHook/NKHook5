#pragma once

#include <string>
#include <magic_enum.hpp>

namespace NKHook5 {
	namespace Signatures {
		enum class Sigs {
			/* CApp */
			/* CAssetBag */
			/* CBaseFactory */
			/* CBasePositionableObject */
			CBasePositionableObject_AssignParent,
			CBasePositionableObject_SetComplete,
			/* CBaseScreen */
			CBaseScreen_CCTOR,
			CBaseScreen_OpenPopup,
			/* CBaseTower */
			/* CBloon */
			CBloon_Update,
			/* CBloonsBaseScreen */
			CBloonsBaseScreen_CCTOR,
			/* CBloonsTD5Game */
			CBloonsTD5Game_CCTOR,
			CBloonsTD5Game_LoadAssets,
			/* CFlagStringConvertor */
			CFlagStringConvertor_FlagToString,
			CFlagStringConvertor_LoadCategory,
			CFlagStringConvertor_StringToFlag,
			/* CFont */
			/* CFontManager */
			CFontManager_GetFont,
			/* CGameSystemPointers */
			/* CLoc */
			CLoc_FindText,
			CLoc_GetText,
			/* Color */
			/* CPlayerProfileV1 */
			CPlayerProfileV1_InternalLoad,
			CPlayerProfileV1_Save,
			/* CPopupScreenBase */
			CPopupScreenBase_CCTOR,
			CPopupScreenBase_AddObject,
			/* CReferenceCounted */
			/* CRenderableTextureObject */
			/* CScreenManager */
			/* CSettingsScreen */
			CSettingsScreen_CCTOR,
			CSettingsScreen_InitLayout,
			/* CTextObject */
			CTextObject_CCTOR_A,
			CTextObject_CCTOR_B,
			CTextObject_CCTOR_C,
			/* CTowerFactory */
			CTowerFactory_CCTOR,
			/* CUnzippedFile */
			CUnzippedFile_CCTOR,
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
			/* ITextureLoaderListener */
			/* Matrix16F */
			/* Screens */
			Screens_GetScreenForParadigm,
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