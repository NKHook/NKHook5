#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CPlayerProfileV1
        {
            class InternalLoad : public IPatch
            {
            public:
                InternalLoad() : IPatch("CPlayerProfileV1::InternalLoad")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc

    } // namespace Patches

} // namespace NKHook5
