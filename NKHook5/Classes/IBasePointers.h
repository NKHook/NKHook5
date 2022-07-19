#ifndef NKHOOK5_CLASSES_IBASEPOINTERS
#define NKHOOK5_CLASSES_IBASEPOINTERS

namespace NKHook5
{
    namespace Classes
    {
        class IBasePointers
        {
		public:
			class CTextureLoader* pCTextureLoader;
			class WinInput* pWinInput;
			class CBloonsTD5Game* pCBloonsTD5Game;
			struct CXmlFontImporter* pCXmlFontImporter;
			struct WinFileIO* pWinFileIO;
			struct CScreenManager* pCScreenManager;
			struct WinSoundManager* pWinSoundManager;
			struct WinMusicManager* pWinMusicManager;
			char pad_0024[12]; //0x0024
			struct SteamStoreInterface* pSteamStoreInterface;
			struct CSteamInterface* pCSteamInterface;
			char pad_0038[4]; //0x0038
			struct CLicensing* pCLicensing;
			char pad_0040[16]; //0x0040
			struct CFacebookInterface* pCFacebookInterface;
			struct CEveryplayInterface* pCEveryplayInterface;
			struct CCurlHttpRequestManager* pCCurlHttpRequestManager;
			char pad_005C[8]; //0x005C
			struct CLoc* pCLoc;
			char pad_0068[8]; //0x0068

		public:
			virtual void Destructor() {};
        };
    } // namespace Classes
    
} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_IBASEPOINTERS */
