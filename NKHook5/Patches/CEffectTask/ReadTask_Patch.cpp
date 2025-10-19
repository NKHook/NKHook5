#include "ReadTask_Patch.h"

#include "../../Utils.h"
#include "../../Signatures/Signature.h"

#include <Util/Macro.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CEffectTask
        {
            using namespace Signatures;

            auto ReadTask_Patch::Apply() -> bool
            {
				const uintptr_t address = std::bit_cast<uintptr_t>(Signatures::GetAddressOf(Sigs::CEffectTask_ReadTask_Patch));
				if (address == 0)
					return false;
				static const uint32_t patchLen = 5;
				this->WriteBytes(address, "\xB8\x00\x00\x00\x00", patchLen);
				return true;
            }
        }
    }
}
