#pragma once

#include "Macro.h"
#include "../../Signatures/Signature.h"

namespace NKHook5::Classes
{
	using namespace Signatures;

	class IBasePointers
	{
	public:
		class CTextureManager* textureManager = nullptr;
		class CTextureLoader* pCTextureLoader = nullptr; //0x0004
		class CInput* pCInput = nullptr; //0x0008
		class CApp* pCApp = nullptr; //0x000C
		class IFontImporter* pIFontImporter = nullptr; //0x0010
		class CBaseFileIO* pCBaseFileIO = nullptr; //0x0014
		class CScreenManager* pCScreenManager = nullptr; //0x0018
		class CSoundManager* pCSoundManager = nullptr; //0x001C
		class CMusicManager* pCMusicManager = nullptr; //0x0020
		char pad_0024[4]; //0x0024
		class SteamStoreInterface* pSteamStoreInterface = nullptr; //0x0028
		class CSteamInterface* pCSteamInterface = nullptr; //0x002C
		char pad_0030[4]; //0x0030
		class CLicensing* pCLicensing = nullptr; //0x0034
		char pad_0038[16]; //0x0038
		class CFacebookInterface* pCFacebookInterface = nullptr; //0x0048
		class CEveryplayInterface* pCEveryplayInterface = nullptr; //0x004C
		class CCurlHttpRequestManager* pCCurlHttpRequestManager = nullptr; //0x0050
		char pad_0054[8]; //0x0054
		class CLoc* pCLoc = nullptr; //0x005C
		char pad_0060[12]; //0x0060

	public:
		IBasePointers() {
			ThisCall<void, IBasePointers*>(Sigs::IBasePointers_CCTOR, this);
		};
	};

	static_assert(sizeof(IBasePointers) == 0x006C);
} // namespace NKHook5::Classes