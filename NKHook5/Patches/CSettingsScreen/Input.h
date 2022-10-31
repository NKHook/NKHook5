#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CSettingsScreen
        {
            class Input : public IPatch
            {
            public:
                Input() : IPatch("CSettingsScreen::Input")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloonsTD5Game

    } // namespace Patches

} // namespace NKHook5
