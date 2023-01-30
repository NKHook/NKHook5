#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CTowerFactory
        {
            class GetTowerInfo : public IPatch
            {
            public:
                GetTowerInfo() : IPatch("CTowerFactory::GetTowerInfo")
                {

                }
                auto Apply() -> bool override;
            };
        }
    }
}