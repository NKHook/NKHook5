#pragma once

#include "Macro.h"
#include "CBaseFactory.h"
#include "CBaseTower.h"
#include "CFlagStringConvertor.h"
#include "boost/shared_ptr"
#include "Vec2F.h"

namespace NKHook5
{
    namespace Signatures {
        namespace CTowerFactory {
            static const char* SIG_CCTOR = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F9 ?? BD ?? ?? ?? ?? ?? BD ?? ?? ?? ?? ?? 45";
        }
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

        class CTowerFactory : public CBaseFactory<struct STowerInfo, CBaseTower>
        {
        public:
            char pad_0004[76]; //0x0004
            CFlagStringConvertor flagStringConvertor; //0x0050
            char pad_0054[236]; //0x0054
        }; //Size: 0x0140
    } // namespace Classes

} // namespace NKHook5