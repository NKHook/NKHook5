#ifndef NKHOOK5_PATCHES_CLOC_RESOLVEBYID
#define NKHOOK5_PATCHES_CLOC_RESOLVEBYID

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            class GetLoc : public IPatch
            {
            public:
                GetLoc() : IPatch("CLoc::GetLoc")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc
        
    } // namespace Patches
    
} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_CLOC_RESOLVEBYID */
