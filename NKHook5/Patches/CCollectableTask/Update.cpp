#include "Update.h"

#include "../../Classes/CCollectableTask.h"
#include "../../ClassesEx/CCollectableTaskExt.h"
#include "../../Signatures/Signature.h"

#include <Logging/Logger.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CCollectableTask
        {
            using namespace Common::Logging;
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::ClassesEx;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func = 0;
            void __fastcall cb_hook(CCollectableTaskExt* pCollectableExt, int pad, float* pSGameTime) {

                PLH::FnCast(o_func, &cb_hook)(pCollectableExt, pad, pSGameTime);
            }

            auto Update::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CCollectableTask_Update);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uintptr_t)address, (const uintptr_t)&cb_hook, &o_func);
                    if(detour->hook())
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
        } // namespace CBloon
    }
}
