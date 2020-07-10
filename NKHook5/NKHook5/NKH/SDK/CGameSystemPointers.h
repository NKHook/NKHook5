#pragma once
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
	char pad_00C4[4]; //0x00C4
	class GameData* GameData; //0x00C8
	char pad_00CC[4]; //0x00CC
	char* CurrentMap; //0x00D0
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
	char pad_0114[1040]; //0x0114

public:
	class CTowerManager& getCTowerManager() {
		return *this->CTowerManager;
	}
	class GameData& getGameData() {
		return *this->GameData;
	}
}; //Size: 0x0124