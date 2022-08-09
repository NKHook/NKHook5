#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CWeapon
        {
            class Fire : public IPatch
            {
            public:
                Fire() : IPatch("CWeapon::Fire")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CWeapon
        
    } // namespace Patches
    
} // namespace NKHook5
