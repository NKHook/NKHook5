#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CApp
        {
            class Init_Debugger_Patch: public IPatch
            {
            public:
				Init_Debugger_Patch() : IPatch("CApp::Init_Debugger_Patch")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CDGSplashScreen
        
    } // namespace Patches
    
} // namespace NKHook5
