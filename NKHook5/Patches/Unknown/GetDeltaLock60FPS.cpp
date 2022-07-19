#include "GetDeltaLock60FPS.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Unknown
        {
            auto GetDeltaLock60FPS::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 83 E4 ?? 83 EC ?? 83 3D");
                const uintptr_t patchLoc = address + 0x1b4;
                static const uint32_t patchLen = 6;
                this->WriteBytes(patchLoc, "\x90\x90\x90\x90\x90\x90", patchLen);
                return true;
            }
        }
    }
}