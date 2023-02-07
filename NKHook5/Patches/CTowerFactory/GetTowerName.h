#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CTowerFactory
        {
            class GetTowerName : public IPatch
            {
            public:
                GetTowerName() : IPatch("CTowerFactory::GetTowerName")
                {

                }
                auto Apply() -> bool override;
            };
        }
    }
}