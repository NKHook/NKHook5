#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CGameScreen
        {
            class Init : public IPatch
            {
            public:
                Init() : IPatch("CGameScreen::Init")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CGameScreen
        
    } // namespace Patches
    
} // namespace NKHook5
