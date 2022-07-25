#ifndef NKHOOK5_PATCHES_OPENGL_SWAPBUFFERS
#define NKHOOK5_PATCHES_OPENGL_SWAPBUFFERS

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace OpenGL
        {
            class Swapbuffers : public IPatch
            {
            public:
                Swapbuffers() : IPatch("OpenGL::Swapbuffers")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace Screens

    } // namespace Patches

} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_OPENGL_SWAPBUFFERS */
