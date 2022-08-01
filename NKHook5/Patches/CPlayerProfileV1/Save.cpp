#include "Save.h"

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
            bool __fastcall cb_hook(Classes::CPlayerProfileV1* profile, int pad, class CBaseFileIO* pFileIO, bool param_2, bool param_3) {
                profile->saveFileName = "Modded.save";
                bool result = PLH::FnCast(o_func, &cb_hook)(profile, pad, pFileIO, param_2, param_3);
                /*SaveData* customData = SaveData::GetInstance();
                for (const auto& [towerId, unlocked] : profile->towerUnlocks) {
                    std::string towerName = g_towerFlags.GetName(towerId);
                    customData->SetTowerUnlocked(towerName, unlocked);
                }
                customData->Save("./Modded.save");*/
                return result;
            }

            auto Save::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CPlayerProfileV1_Save);
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