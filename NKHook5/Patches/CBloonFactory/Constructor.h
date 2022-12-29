#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonFactory
        {
            class Constructor : public IPatch
            {
            public:
                Constructor() : IPatch("CBloonFactory::Constructor")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace FlagToString
        
    } // namespace Patches
    
} // namespace NKHook5
