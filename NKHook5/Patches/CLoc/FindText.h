#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

#undef FindText

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            class FindText : public IPatch
            {
            public:
                FindText() : IPatch("CLoc::FindText")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc

    } // namespace Patches

} // namespace NKHook5
