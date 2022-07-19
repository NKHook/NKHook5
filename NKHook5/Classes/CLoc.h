#ifndef NKHOOK5_CLASSES_CLOC
#define NKHOOK5_CLASSES_CLOC

#include <ghstl/string>

namespace NKHook5
{
    namespace Classes
    {
        struct SLoc {
            uint32_t key; //0x0000
            ghstl::string id; //0x0004
            int32_t l; //0x001C
            ghstl::string val; //0x0020
        };

        class CLoc
        {
            
        };
    } // namespace Classes

} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_CLOC */