#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBaseFileIO
        {
            class OpenFile : public IPatch
            {
            public:
                OpenFile() : IPatch("CBaseFileIO::OpenFile")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc

    } // namespace Patches

} // namespace NKHook5
