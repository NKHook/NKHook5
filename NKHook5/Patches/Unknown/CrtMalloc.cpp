#include "CrtMalloc.h"

#include "../../Signatures/Signature.h"
#include "../../Classes/CProjectile.h"
#include "../../ClassesEx/CProjectileExt.h"
#include "../../Classes/CCollectableTask.h"
#include "../../ClassesEx/CCollectableTaskExt.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Unknown
        {
            using namespace Signatures;

            static uint64_t o_func;
            void* __cdecl hkMalloc(size_t size) {
                if (size == sizeof(Classes::CProjectile)) {
                    size = sizeof(ClassesEx::CProjectileExt);
                }
                if (size == sizeof(Classes::CCollectableTask)) {
                    size = sizeof(ClassesEx::CCollectableTaskExt);
                }
                return PLH::FnCast(o_func, &hkMalloc)(size);
            }

            auto CrtMalloc::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CRT_operator_new);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&hkMalloc, &o_func);
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