#include "GetScreenForParadigm.h"

#include <ghstl/string>
#include "../../Classes/CGameSystemPointers.h"
#include "../../Classes/CBloonsBaseScreen.h"
#include "../../Classes/CPopupScreenBase.h"
#include "../../Classes/DeviceType.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Screens
        {
            uint64_t o_func;
            namespace Exports {
                Classes::CBloonsBaseScreen* __fastcall fGetScreenForParadigm(ghstl::string* screenName, Classes::eDeviceType deviceType, Classes::CGameSystemPointers* pCGameSystemPointers) {
                    /*std::string cppScreenName = screenName->cpp_str();
                    static Classes::CPopupScreenBase* nkhookInfoScreen;
                    static ghstl::string nkhookInfoScreenName = "NKHookInfoScreen";
                    if (cppScreenName == nkhookInfoScreenName.cpp_str()) {
                        if (!nkhookInfoScreen) {
                            nkhookInfoScreen = new Classes::CPopupScreenBase(pCGameSystemPointers, &nkhookInfoScreenName);
                        }
                        return nkhookInfoScreen;
                    }*/
                    return PLH::FnCast(o_func, &fGetScreenForParadigm)(screenName, deviceType, pCGameSystemPointers);
                }
            }

            auto GetScreenForParadigm::Apply() -> bool
            {
                const uintptr_t address = NKHook5::Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 8B ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? 45 ?? ?? ?? ?? ?? 83");
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&Exports::fGetScreenForParadigm, &o_func);
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