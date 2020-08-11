#pragma once
// Created with ReClass.NET 1.2 by KN4CK3R

class IBasePointers
{
public:
	char pad_0000[8]; //0x0000
	class CTextureLoader* CTextureLoader; //0x0008
	class WinInput* WinInput; //0x000C
	class CBloonsTD5Game* CBloonsTD5Game; //0x0010
	char pad_0014[4]; //0x0014
	class WinFileIO* WinFileIO; //0x0018
	class CScreenManager* CScreenManager; //0x001C
	class WinSoundManager* WinSoundManager; //0x0020
	class WinMusicManager* WinMusicManager; //0x0024
	char pad_0028[4]; //0x0028
	class SteamStoreInterface* SteamStoreInterface; //0x002C
	class CSteamInterface* CSteamInterface; //0x0030
	char pad_0034[4]; //0x0034
	class CLicensing* CLicensing; //0x0038
	char pad_003C[16]; //0x003C
	class CFacebookInterface* CFacebookInterface; //0x004C
	class CEveryplayInterface* CEveryplayInterface; //0x0050
	class CCurlHttpRequestManager* CCurlHttpRequestManager; //0x0054
	char pad_0058[8]; //0x0058
	class CLoc* CLoc; //0x0060
	char pad_0064[12];

public:
	IBasePointers() {
		Constructor(this);
	}
	void Constructor(IBasePointers* self);
	//0x0064
}; //Size: 0x0070