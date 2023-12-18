#pragma once

#include <boost/shared_ptr.hpp>

#include "Macro.h"
#include "CBaseFactory.h"
#include "CBaseTower.h"
#include "CFlagStringConvertor.h"
#include "Vec2F.h"
#include "STowerInfo.h"

#define MAX_TOWER_ID (static_cast<uint64_t>(NKHook5::Classes::TowerIDs::GameDummy))

namespace NKHook5
{
	namespace Signatures::CTowerFactory {
		static const char* SIG_CCTOR = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F9 ?? BD ?? ?? ?? ?? ?? BD ?? ?? ?? ?? ?? 45";
	};

    namespace Classes
    {
        enum class TowerFlagCategories {
            HARD_TOWER_ID = 0,
            TARGETING_MODE = 1,
            AIRCRAFT_TARGET_MODE = 3,
            AGENT_STATUS = 4,
            TOWER_ID = 5
        };

        enum class TowerIDs : uint64_t {
            TestTower = 1ull << 1ull,
            DartMonkey = 1ull << 2ull,
            TackTower = 1ull << 3ull,
            SniperMonkey = 1ull << 4ull,
            BoomerangThrower = 1ull << 5ull,
            NinjaMonkey = 1ull << 6ull,
            BombTower = 1ull << 7ull,
            IceTower = 1ull << 8ull,
            GlueGunner = 1ull << 9ull,
            MonkeyBuccaneer = 1ull << 10ull,
            MonkeyAce = 1ull << 11ull,
            SuperMonkey = 1ull << 12ull,
            MonkeyApprentice = 1ull << 13ull,
            MonkeyVillage = 1ull << 14ull,
            BananaFarm = 1ull << 15ull,
            MortarTower = 1ull << 16ull,
            DartlingGun = 1ull << 17ull,
            SpikeFactory = 1ull << 18ull,
            HeliPilot = 1ull << 19ull,
            RoadSpikes = 1ull << 20ull,
            ExplodingPineapple = 1ull << 21ull,
            MonkeyEngineer = 1ull << 22ull,
            Bloonchipper = 1ull << 23ull,
            MonkeySub = 1ull << 24ull,
            MeerkatSpyPro = 1ull << 25ull,
            MeerkatSpy = 1ull << 26ull,
            TribalTurtlePro = 1ull << 27ull,
            TribalTurtle = 1ull << 28ull,
            PortableLakePro = 1ull << 29ull,
            PortableLake = 1ull << 30ull,
            PontoonPro = 1ull << 31ull,
            Pontoon = 1ull << 32ull,
            BloonsdayDevicePro = 1ull << 33ull,
            BloonsdayDevice = 1ull << 34ull,
            AngrySquirrelPro = 1ull << 35ull,
            AngrySquirrel = 1ull << 36ull,
            SuperMonkeyStormPro = 1ull << 37ull,
            SuperMonkeyStorm = 1ull << 38ull,
            BeeKeeperPro = 1ull << 39ull,
            BeeKeeper = 1ull << 40ull,
            BloonberryBushPro = 1ull << 41ull,
            BloonberryBush = 1ull << 42ull,
            RadadactylPro = 1ull << 43ull,
            Radadactyl = 1ull << 44ull,
            BananaFarmerPro = 1ull << 45ull,
            BananaFarmer = 1ull << 46ull,
            WizardLord = 1ull << 47ull,
            AcePlane = 1ull << 48ull,
            AircraftCarrier = 1ull << 49ull,
            PhoenixPlane = 1ull << 50ull,
            SuperPhoenixPlane = 1ull << 51ull,
            SupplyDropPlane = 1ull << 52ull,
            HeliPilotAircraft = 1ull << 53ull,
            RadadactylPlane = 1ull << 54ull,
            RadderdactylPlane = 1ull << 55ull,
            MonkeyEngineerSentry = 1ull << 56ull,
            MonkeyEngineerSentryTier4 = 1ull << 57ull,
            GameDummy = 1ull << 58ull,
        };

        class CTowerFactory : public CBaseFactory<STowerInfo, CBaseTower>, public CFlagStringConvertor
        {
        public:
            char pad_0060[72]; //0x0060

			STowerInfo* GetTowerInfo(TowerIDs id)
			{
				return ThisCall<Sigs::CTowerFactory_GetTowerInfo, &CTowerFactory::GetTowerInfo>(this, id);
			}
        }; //Size: 0x0A4

        static_assert(sizeof(CBaseFactory<STowerInfo, CBaseTower>) == 0x50);
        static_assert(sizeof(CFlagStringConvertor) == 0xC);
        static_assert(sizeof(CTowerFactory) == 0xA4);
    } // namespace Classes

} // namespace NKHook5