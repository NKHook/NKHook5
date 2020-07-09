#pragma once
class CBloonsTD5Game
{
public:
	char pad_0000[12]; //0x0000
	class CTextureLoader* CTextureLoader; //0x000C
	class WinInput* WinInput; //0x0010
	class CBloonsTD5Game* Self; //0x0014
	char pad_0018[4]; //0x0018
	class WinFileIO* WinFileIO; //0x001C
	class CScreenManager* CScreenManager; //0x0020
	class WinSoundManager* WinSoundManager; //0x0024
	class WinMusicManager* WinMusicManager; //0x0028
	char pad_002C[4]; //0x002C
	class SteamStoreInterface* SteamStoreInterface; //0x0030
	class CSteamInterface* CSteamInterface; //0x0034
	char pad_0038[4]; //0x0038
	class CLicensing* CLicensing; //0x003C
	char pad_0040[16]; //0x0040
	class CFacebookInterface* CFacebookInterface; //0x0050
	class CEveryplayInterface* CEveryplayInterface; //0x0054
	class CCurlHttpRequestManager* CCurlHttpRequestManager; //0x0058
	char pad_005C[8]; //0x005C
	class CLoc* CLoc; //0x0064
	char pad_0068[16]; //0x0068
	class CMemoryTracker* CMemoryTracker; //0x0078
	class CTimerTracker* CTimerTracker; //0x007C
	class CTimerTrackerGraph* CTimerTrackerGraph; //0x0080
	char pad_0084[192]; //0x0084
	class CAssetBag* CAssetBag; //0x0144
	char pad_0148[4]; //0x0148
	class CGameSystemPointers* CGameSystemPointers; //0x014C
	char pad_0150[4]; //0x0150
	class CFont* CFont; //0x0154
	char pad_0158[4]; //0x0158
	class CTextObject* CTextObject; //0x015C
	class CTextObject* N0000030D; //0x0160
	char pad_0164[212]; //0x0164
}; //Size: 0x0238