#include "GetScreenForParadigm.h"

#include <ghstl/string>
#include "../../Classes/CGameSystemPointers.h"
#include "../../Classes/CBloonsBaseScreen.h"
#include "../../Classes/CPopupScreenBase.h"
#include "../../Classes/DeviceType.h"
#include "../../Signatures/Signature.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace Screens
        {
            using namespace Signatures;

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
                    //return ((Classes::CBloonsBaseScreen*(__cdecl*)(void*, Classes::eDeviceType, void*))o_func)(screenName, deviceType, pCGameSystemPointers);
                    return PLH::FnCast(o_func, &fGetScreenForParadigm)(screenName, deviceType, pCGameSystemPointers);
                }
            }

            auto GetScreenForParadigm::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::Screens_GetScreenForParadigm);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&Exports::fGetScreenForParadigm, &o_func);
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