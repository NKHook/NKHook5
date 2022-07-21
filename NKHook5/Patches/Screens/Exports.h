#ifndef NKHOOK5_PATCHES_SCREENS_EXPORTS
#define NKHOOK5_PATCHES_SCREENS_EXPORTS

#include "../../Classes/CGameSystemPointers.h"
#include "../../Classes/CBloonsBaseScreen.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Screens
        {
            namespace Exports {
                extern Classes::CBloonsBaseScreen* __fastcall fGetScreenForParadigm(ghstl::string* screenName, int deviceType, Classes::CGameSystemPointers* pCGameSystemPointers)
            };
        } // namespace Screens

    } // namespace Patches

} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_SCREENS_EXPORTS */
