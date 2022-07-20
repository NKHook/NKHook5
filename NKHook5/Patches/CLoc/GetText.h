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
            class GetText : public IPatch
            {
            public:
                GetText() : IPatch("CLoc::GetText")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace CLoc
        
    } // namespace Patches
    
} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_CLOC_RESOLVEBYID */
