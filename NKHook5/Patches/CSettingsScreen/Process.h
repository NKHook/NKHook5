#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CSettingsScreen
        {
            class Process : public IPatch
            {
            public:
                Process() : IPatch("CSettingsScreen::Process")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloonsTD5Game

    } // namespace Patches

} // namespace NKHook5
