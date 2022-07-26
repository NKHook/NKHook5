#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace GLRenderLayer
        {
            class Draw : public IPatch
            {
            public:
                Draw() : IPatch("GLRenderLayer::Draw")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace Screens

    } // namespace Patches

} // namespace NKHook5
