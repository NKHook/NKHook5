#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CPlayerProfileV1
        {
            class Save : public IPatch
            {
            public:
                Save() : IPatch("CPlayerProfileV1::Save")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc

    } // namespace Patches

} // namespace NKHook5
