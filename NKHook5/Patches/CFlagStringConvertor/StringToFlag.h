#ifndef NKHOOK5_PATCHES_CFLAGSTRINGCONVERTOR_STRINGTOFLAG
#define NKHOOK5_PATCHES_CFLAGSTRINGCONVERTOR_STRINGTOFLAG

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            class StringToFlag : public IPatch
            {
            public:
                StringToFlag() : IPatch("CFlagStringConvertor::StringToFlag")
                {

                }
                auto Apply() -> bool override;
            };
        } // namespace FlagToString
        
    } // namespace Patches
    
} // namespace NKHook5
#endif /* NKHOOK5_PATCHES_CFLAGSTRINGCONVERTOR_STRINGTOFLAG */
