#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CProjectile
        {
            class Update : public IPatch
            {
            public:
                Update() : IPatch("CProjectile::Update")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloon
        
    } // namespace Patches
} // namespace NKHook5
