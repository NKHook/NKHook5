#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsBaseScreen
        {
            class Init : public IPatch
            {
            public:
                Init() : IPatch("CBloonsBaseScreen::Init")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CGameScreen
        
    } // namespace Patches
    
} // namespace NKHook5
