#include "InternalLoad.h"

#include "../../Classes/CPlayerProfileV1.h"
#include "../../Mod/SaveData.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"

extern NKHook5::Util::FlagManager g_towerFlags;

namespace NKHook5
{
    namespace Patches
    {
        namespace CPlayerProfileV1
        {
            using namespace Mod;
            using namespace Signatures;

            static uint64_t o_func;
            bool __fastcall cb_hook(Classes::CPlayerProfileV1* profile, int pad, class CBaseFileIO* pFileIO, ghstl::string fileName, bool param_3) {
                bool result = PLH::FnCast(o_func, &cb_hook)(profile, pad, pFileIO, fileName, param_3);
                /*SaveData* customData = SaveData::GetInstance();
                customData->Load("./Modded.save");*/
                //Add all towers to the profile
                printf("Adding all towers to save...\n");
                const auto& allTowerFlags = g_towerFlags.GetAll();
                for (const auto& pair : allTowerFlags) {
                    profile->towerUnlocks[pair.first] = true;// customData->IsTowerUnlocked(pair.second);
                    printf("Added tower with ID '%llx' to save\n", pair.first);
                }
                printf("Done!\n");
                return result;
            }

            auto InternalLoad::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CPlayerProfileV1_InternalLoad);
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