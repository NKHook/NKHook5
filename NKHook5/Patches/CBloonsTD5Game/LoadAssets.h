#ifndef NKHOOK5_PATCHES_CBLOONSTD5GAME_LOADASSETS
#define NKHOOK5_PATCHES_CBLOONSTD5GAME_LOADASSETS

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            class LoadAssets : public IPatch
            {
            public:
                LoadAssets() : IPatch("CBloonsTD5Game::LoadAssets")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloonsTD5Game
        
    } // namespace Patches
    
} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_CBLOONSTD5GAME_LOADASSETS */
