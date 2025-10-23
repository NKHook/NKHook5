#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace C_GameSFXManager
        {
            class Play : public IPatch
            {
				void cb_hook(int audio);
            public:
                Play() : IPatch("C_GameSFXManager::Play") {}
                auto Apply() -> bool override;
            };
        } // namespace CWeapon
        
    } // namespace Patches
    
} // namespace NKHook5
