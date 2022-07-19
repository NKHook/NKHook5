#ifndef NKHOOK5_PATCHES_IPATCH
#define NKHOOK5_PATCHES_IPATCH

#include <string>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/ZydisDisassembler.hpp>

namespace NKHook5
{
    namespace Patches
    {
        class IPatch
        {
            static inline PLH::ZydisDisassembler* dis = new PLH::ZydisDisassembler(PLH::Mode::x86);
            std::string name;
        public:
            IPatch(std::string name);
            auto GetName() -> std::string;
            auto GetDis() -> PLH::ZydisDisassembler&;
            virtual auto Apply() -> bool;
        };
    } // namespace Patches
    
} // namespace NKHook5

#endif /* NKHOOK5_PATCHES_IPATCH */
