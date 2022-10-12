#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBaseFileIO
        {
            class FileExists : public IPatch
            {
            public:
                FileExists() : IPatch("CBaseFileIO::FileExists")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc

    } // namespace Patches

} // namespace NKHook5
