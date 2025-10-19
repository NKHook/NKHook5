#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CEffectTask
        {
            class ReadTask_Patch : public IPatch
            {
            public:
                ReadTask_Patch() : IPatch("CEffectTask::ReadTask_Patch")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CDGSplashScreen
        
    } // namespace Patches
    
} // namespace NKHook5
