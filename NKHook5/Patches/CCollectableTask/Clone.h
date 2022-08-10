#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CCollectableTask
        {
            class Clone : public IPatch
            {
            public:
                Clone() : IPatch("CCollectableTask::Clone")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloon
        
    } // namespace Patches
} // namespace NKHook5
