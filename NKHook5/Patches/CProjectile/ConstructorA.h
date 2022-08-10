#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CProjectile
        {
            class ConstructorA : public IPatch
            {
            public:
                ConstructorA() : IPatch("CProjectile::ConstructorA")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloon
        
    } // namespace Patches
} // namespace NKHook5
