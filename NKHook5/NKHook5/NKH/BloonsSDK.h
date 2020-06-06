#pragma once
#include "pch.h"
// Created with ReClass.NET 1.2 by KN4CK3R

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

class CTextureLoader
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class WinInput
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class WinFileIO
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CScreenManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class WinSoundManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class WinMusicManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class SteamStoreInterface
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CSteamInterface
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CLicensing
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CFacebookInterface
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CEveryplayInterface
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CCurlHttpRequestManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CLoc
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CMemoryTracker
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CTimerTracker
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CTimerTrackerGraph
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CAssetBag
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CGameSystemPointers
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
	char pad_0064[16]; //0x0064
	class CBloonManager* CBloonManager; //0x0074
	class CWeaponTaskManager* CWeaponTaskManager; //0x0078
	class CTowerManager* CTowerManager; //0x007C
	char pad_0080[8]; //0x0080
	class CAircraftManager* CAircraftManager; //0x0088
	class CManualWeaponManager* CManualWeaponManager; //0x008C
	char pad_0090[8]; //0x0090
	class CDailyQuestManager* CDailyQuestManager; //0x0098
	char pad_009C[4]; //0x009C
	class CTowerFactory* CTowerFactory; //0x00A0
	class CWeaponFactory* CWeaponFactory; //0x00A4
	char pad_00A8[4]; //0x00A8
	class CBloonFactory* CBloonFactory; //0x00AC
	class CRoundFactory* CRoundFactory; //0x00B0
	class CUpgradeFactory* CUpgradeFactory; //0x00B4
	class CSpecialtyFactory* CSpecialtyFactory; //0x00B8
	class CLabFactory* CLabFactory; //0x00BC
	class CBloonAbilityFactory* CBloonAbilityFactory; //0x00C0
	char pad_00C4[16]; //0x00C4
	class CSteamCloud* CSteamCloud; //0x00D4
	char pad_00D8[8]; //0x00D8
	class CSocialLeaderboard* CSocialLeaderboard; //0x00E0
	char pad_00E4[4]; //0x00E4
	class DGAnalytics_Redshift* DGAnalytics_Redshift; //0x00E8
	char pad_00EC[12]; //0x00EC
	class CTheCrucibleManager* CTheCrucibleManager; //0x00F8
	class CMixNMatchManager* CMixNMatchManager; //0x00FC
	class CPreferredMonkeyManager* CPreferredMonkeyManager; //0x0100
	class CMonkeyTeamManager* CMonkeyTeamManager; //0x0104
	char pad_0108[4]; //0x0108
	class CProjectileSkinDataList* CProjectileSkinDataList; //0x010C
	class CProjectileSkinDataList* CProjectileSkinDataList2; //0x0110
	char pad_0114[12]; //0x0114
}; //Size: 0x0120

class CFont
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CTextObject
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N000008A9
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N000008CF
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N000008F5
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N0000091B
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N00000941
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N00000967
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N000009B0
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CBloonManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CWeaponTaskManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CTowerManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CAircraftManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CManualWeaponManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CDailyQuestManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CFlagStringConvertor
{
public:
	char pad_0004[92]; //0x0004

	virtual void Destructor();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
}; //Size: 0x0060

class CTowerFactory
{
public:
	char pad_0000[80]; //0x0000
	class CFlagStringConvertor CFlagStringConvertor; //0x0050
	char pad_00B0[176]; //0x00B0
}; //Size: 0x0160

class CWeaponFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CBloonFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CRoundFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CUpgradeFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CSpecialtyFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CLabFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CBloonAbilityFactory
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CSteamCloud
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CSocialLeaderboard
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class DGAnalytics_Redshift
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CTheCrucibleManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CMixNMatchManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CPreferredMonkeyManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CMonkeyTeamManager
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class CProjectileSkinDataList
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N00000D99
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004