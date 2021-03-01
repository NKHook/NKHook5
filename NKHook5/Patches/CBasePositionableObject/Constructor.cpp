#include "Constructor.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CBasePositionableObject
        {
            uint64_t o_func;
            uint64_t totalCreations = 0;
            void* __fastcall cb_hook(void* object) {
                totalCreations++;
                std::string typeName = NKHook5::Utils::GetTypeName(object);
                std::cout << "Object created at: " << object << " of type: " << typeName << " Total creations: " << totalCreations << std::endl;
                return PLH::FnCast(o_func, &cb_hook)(object);
            }

            auto Constructor::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("56 57 8B F9 0F 57 ?? 8D");
                if(address)
                {
                    PLH::x86Detour detour(address, (const uintptr_t)&cb_hook, &o_func, GetDis());
                    if(detour.hook())
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
        } // namespace CBasePositionableObject
    }
}
