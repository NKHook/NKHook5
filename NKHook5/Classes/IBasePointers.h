#ifndef NKHOOK5_CLASSES_IBASEPOINTERS
#define NKHOOK5_CLASSES_IBASEPOINTERS

#include "CBloonsTD5Game.h"

namespace NKHook5
{
    namespace Classes
    {
        class IBasePointers
        {
		public:
			struct CTextureLoader * CTextureLoader;
			struct WinInput * WinInput;
			CBloonsTD5Game* CBloonsTD5Game;
			struct CXmlFontImporter * CXmlFontImporter;
			struct WinFileIO* WinFileIO;
			struct CScreenManager* CScreenManager;
			struct WinSoundManager* WinSoundManager;
			struct WinMusicManager* WinMusicManager;
			char pad_0024[12]; //0x0024
			struct SteamStoreInterface* SteamStoreInterface;
			struct CSteamInterface* CSteamInterface;
			char pad_0038[4]; //0x0038
			struct CLicensing;
			char pad_0040[16]; //0x0040
			struct CFacebookInterface;
			struct CEveryplayInterface;
			struct CCurlHttpRequestManager;
			char pad_005C[8]; //0x005C
			struct CLoc;
			char pad_0068[8]; //0x0068

		public:
			virtual void Destructor() {};
        };
    } // namespace Classes
    
} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_IBASEPOINTERS */
