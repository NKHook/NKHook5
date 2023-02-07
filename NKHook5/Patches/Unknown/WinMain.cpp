#include "WinMain.h"

#include "../../Signatures/Signature.h"
#include <Windows.h>
#include <filesystem>

#include <Logging/Logger.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace Unknown
        {
            using namespace Signatures;
            using namespace Common::Logging::Logger;

            uint64_t o_func;
            void __stdcall hkWinMain(HINSTANCE param_1, HINSTANCE param_2, char* argv, int nShowCmd) {
                if (argv != nullptr) {
                    Print(LogLevel::DEBUG, "CMDLINE: %s", argv);
                    argv[0] = 0;
                    argv[1] = 0;
                    Print(LogLevel::DEBUG, "Cleared CMDLINE");
                }
                else {
                    Print(LogLevel::DEBUG, "CMDLINE has not been cleared");
                }
                return PLH::FnCast(o_func, &hkWinMain)(param_1, param_2, argv, nShowCmd);
            }

            auto WinMain::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::Unknown_WinMain);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&hkWinMain, &o_func);
                    if (detour->hook())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
    }
}