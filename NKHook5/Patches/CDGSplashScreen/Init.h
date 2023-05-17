#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CDGSplashScreen
        {
            class Init : public IPatch
            {
            public:
                Init() : IPatch("CDGSplashScreen::Init")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CDGSplashScreen
        
    } // namespace Patches
    
} // namespace NKHook5
