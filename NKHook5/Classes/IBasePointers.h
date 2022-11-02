#ifndef NKHOOK5_CLASSES_IBASEPOINTERS
#define NKHOOK5_CLASSES_IBASEPOINTERS

#include "Macro.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Classes
    {
		using namespace Signatures;

        class IBasePointers
        {
		public:
			class CTextureManager* textureManager;
			class CTextureLoader* pCTextureLoader; //0x0004
			class CInput* pCInput; //0x0008
			class CApp* pCApp; //0x000C
			class IFontImporter* pIFontImporter; //0x0010
			class CBaseFileIO* pCBaseFileIO; //0x0014
			class CScreenManager* pCScreenManager; //0x0018
			class CSoundManager* pCSoundManager; //0x001C
			class CMusicManager* pCMusicManager; //0x0020
			char pad_0024[4]; //0x0024
			class SteamStoreInterface* pSteamStoreInterface; //0x0028
			class CSteamInterface* pCSteamInterface; //0x002C
			char pad_0030[4]; //0x0030
			class CLicensing* pCLicensing; //0x0034
			char pad_0038[16]; //0x0038
			class CFacebookInterface* pCFacebookInterface; //0x0048
			class CEveryplayInterface* pCEveryplayInterface; //0x004C
			class CCurlHttpRequestManager* pCCurlHttpRequestManager; //0x0050
			char pad_0054[8]; //0x0054
			class CLoc* pCLoc; //0x005C
			char pad_0060[12]; //0x0060

		public:
			IBasePointers() {
				ThisCall<void, IBasePointers*>(Sigs::IBasePointers_CCTOR, this);
			};
        };

		static_assert(sizeof(IBasePointers) == 0x006C);
    } // namespace Classes
    
} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_IBASEPOINTERS */
