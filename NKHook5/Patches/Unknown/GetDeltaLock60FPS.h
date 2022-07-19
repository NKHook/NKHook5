#ifndef NKHOOK5_PATCHES_UNKNOWN_GETDELTALOCK60FPS
#define NKHOOK5_PATCHES_UNKNOWN_GETDELTALOCK60FPS

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Unknown
        {
            class GetDeltaLock60FPS : public IPatch
            {
            public:
                GetDeltaLock60FPS() : IPatch("Unknown::GetDeltaLock60FPS")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace Unknown

    } // namespace Patches

} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_UNKNOWN_GETDELTALOCK60FPS */
