#include "Init_Debugger_Patch.h"

#include "../../Utils.h"
#include "../../Signatures/Signature.h"

#include <Util/Macro.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CApp
        {
            using namespace Signatures;

            auto Init_Debugger_Patch::Apply() -> bool
            {
				const uintptr_t address = std::bit_cast<uintptr_t>(Signatures::GetAddressOf(Sigs::CApp_Init_Debugger_Patch));
				if (address == 0)
					return false;
				static const uint32_t patchLen = 6;
				this->WriteBytes(address, "\xB8\x00\x00\x00\x00\x90", patchLen);
				return true;
            }
        }
    }
}
