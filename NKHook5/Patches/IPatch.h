#ifndef IPATCH
#define IPATCH

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
            std::string name;
        public:
            IPatch(std::string name)
            {
                this->name = name;
            }
            auto GetName() -> std::string
            {
                return this->name;
            }
            auto GetDis() -> PLH::CapstoneDisassembler
            {
                PLH::CapstoneDisassembler dis(PLH::Mode::x86);
                return dis;
            }
            virtual auto Apply() -> bool;
        };
    } // namespace Patches
    
} // namespace NKHook5
#endif /* IPATCH */
