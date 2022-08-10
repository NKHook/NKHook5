#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CProjectile
        {
            class Clone : public IPatch
            {
            public:
                Clone() : IPatch("CProjectile::Clone")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloon
        
    } // namespace Patches
} // namespace NKHook5
