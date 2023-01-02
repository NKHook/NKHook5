#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CTextureManager
        {
            class GetSpriteInfoPtr : public IPatch
            {
            public:
                GetSpriteInfoPtr() : IPatch("CTextureManager::GetSpriteInfoPtr")
                {

                }
                auto Apply() -> bool override;
            };
        }

    }

}
