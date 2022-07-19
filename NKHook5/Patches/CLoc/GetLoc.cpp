#include "GetLoc.h"

#include <ghstl/string>
#include <string>
#include "../../Classes/CLoc.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CLoc
        {
            uint64_t o_func;
            Classes::SLoc* __fastcall cb_hook(Classes::CLoc* pCLoc, uint32_t pad, ghstl::string* locId, int len) {
                Classes::SLoc* result = PLH::FnCast(o_func, &cb_hook)(pCLoc, pad, locId, len);

                //std::cin.get();
                if (result) {
                    if (result->val.cpp_str() == "LOC_SETTINGS_Copyright") {
                        std::string verTxt = result->val.cpp_str();
                        verTxt += "\nNKHook5 made by DisabledMallis";
                        result->val.assign(verTxt);
                    }
                }
                //result->val.assign("Yoink");

                return result;
            }

            auto GetLoc::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 8B ?? ?? 8B ?? ?? 85 FF");
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
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
        }
    }
}