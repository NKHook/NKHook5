#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CSettingsScreen
        {
            class InitLayout : public IPatch
            {
            public:
                InitLayout() : IPatch("CSettingsScreen::InitLayout")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloonsTD5Game
        
    } // namespace Patches
    
} // namespace NKHook5
