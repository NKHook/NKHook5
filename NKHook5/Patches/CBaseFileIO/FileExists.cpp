#include "FileExists.h"

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

            /* THIS METHOD DOES NOT WORK, IGNORE */

            static uint64_t o_func;
            bool __fastcall cb_hook(Classes::CBaseFileIO* pCBaseFileIO, int pad, std::string* path, int policy) {
                //return PLH::FnCast(o_func, &cb_hook)(pCBaseFileIO, pad, path, policy);
                
                //check if the game is looking for a font, those can only be loaded from disk 
                if (path->find("Assets/Fonts") != std::string::npos) {
                    return PLH::FnCast(o_func, cb_hook)(pCBaseFileIO, pad, path, policy);
                }

                //Its easier to replace file content if we make the game think its loaded from the zip file
                //replacing contents of files on disk in memory is a little bit of a hassle
                //so by returning false we effectively tell the game that the files do not exist on disk, and only in the jet file
                return false;
            }

            auto FileExists::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CBaseFileIO_FileExists);
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