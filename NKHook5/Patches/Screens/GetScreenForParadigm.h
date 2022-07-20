#ifndef NKHOOK5_PATCHES_SCREENS_GETSCREENFORPARADIGM
#define NKHOOK5_PATCHES_SCREENS_GETSCREENFORPARADIGM

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Screens
        {
            class GetScreenForParadigm : public IPatch
            {
            public:
                GetScreenForParadigm() : IPatch("Screens::GetScreenForParadigm")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace Screens

    } // namespace Patches

} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_SCREENS_GETSCREENFORPARADIGM */
