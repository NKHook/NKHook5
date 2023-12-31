#pragma once

#include "../../Classes/CBloon.h"

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloon
        {
            class Update : public IPatch
            {
				void cb_hook(float* pSGameTime);
            public:
                Update() : IPatch("CBloon::Update")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloon
        
    } // namespace Patches
    
} // namespace NKHook5
