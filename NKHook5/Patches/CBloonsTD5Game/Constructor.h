#ifndef CONSTRUCTOR
#define CONSTRUCTOR

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonsTD5Game
        {
            class Constructor : public IPatch
            {
            public:
                Constructor() : IPatch("CBloonsTD5Game::Constructor")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CBloonsTD5Game
        
    } // namespace Patches
    
} // namespace NKHook5
#endif /* CONSTRUCTOR */
