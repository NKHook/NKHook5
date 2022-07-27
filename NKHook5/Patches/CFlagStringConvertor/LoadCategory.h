#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            class LoadCategory : public IPatch
            {
            public:
                LoadCategory() : IPatch("CFlagStringConvertor::LoadCategory")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace FlagToString
        
    } // namespace Patches
    
} // namespace NKHook5
