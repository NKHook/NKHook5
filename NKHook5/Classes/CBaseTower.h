#pragma once

#include "CBasePositionableObject.h"
#include "CBloonEscapedEvent.h"
#include "CObserver.h"
#include "CTowerRemovedEvent.h"

namespace NKHook5
{
    namespace Classes
    {
        class CBaseTower :
            public CBasePositionableObject,
            public CObserver<CBloonEscapedEvent>,
            public CObserver<CTowerRemovedEvent>
        {
        public:
            char pad_00B8[52]; //0x00B8
            int32_t popCount; //0x00EC
            char pad_00F0[468]; //0x00F0

            virtual ~CBaseTower() {};
        };

        static_assert(sizeof(CObserver<CBloonEscapedEvent>) == 0x8);
        static_assert(sizeof(CObserver<CTowerRemovedEvent>) == 0x8);
        //static_assert(sizeof(CBaseTower) == 0x2C4);
    } // namespace Classes
} // namespace NKHook5
