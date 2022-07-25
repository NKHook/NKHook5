#ifndef NKHOOK5_PATCHES_CFLAGSTRINGCONVERTOR_FLAGTOSTRING
#define NKHOOK5_PATCHES_CFLAGSTRINGCONVERTOR_FLAGTOSTRING

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            class FlagToString : public IPatch
            {
            public:
                FlagToString() : IPatch("CFlagStringConvertor::FlagToString")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace FlagToString
        
    } // namespace Patches
    
} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_CFLAGSTRINGCONVERTOR_FLAGTOSTRING */
