#ifndef NKHOOK5_PATCHES_IPATCH
#define NKHOOK5_PATCHES_IPATCH

#include <string>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>

#pragma comment(lib,"asmjit.lib")
#pragma comment(lib,"capstone.lib")
#pragma comment(lib,"PolyHook_2.lib")
#pragma comment(lib,"Zydis.lib")
#pragma comment(lib,"Zycore.lib")

namespace NKHook5
{
    namespace Patches
    {
        class IPatch
        {
            static inline PLH::CapstoneDisassembler* dis = new PLH::CapstoneDisassembler(PLH::Mode::x86);
            std::string name;
        public:
            IPatch(std::string name);
            auto GetName() -> std::string;
            auto GetDis() -> PLH::CapstoneDisassembler&;
            virtual auto Apply() -> bool;
        };
    } // namespace Patches
    
} // namespace NKHook5

#endif /* NKHOOK5_PATCHES_IPATCH */
