#include "OpenFile.h"

#include "../../Classes/CBaseFileIO.h"
#include "../../Classes/IFile.h"
#include "../../Signatures/Signature.h"

#include <string>

namespace NKHook5
{
    namespace Patches
    {
        namespace CBaseFileIO
        {
            using namespace NKHook5;
            using namespace NKHook5::Signatures;

            static uint64_t o_func;
            Classes::IFile* __fastcall cb_hook(Classes::CBaseFileIO* pCBaseFileIO, int pad, std::string* path, int policy, int eFileOpenMode) {
                return PLH::FnCast(o_func, &cb_hook)(pCBaseFileIO, pad, path, policy, eFileOpenMode);
            }

            auto OpenFile::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CBaseFileIO_OpenFile);
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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