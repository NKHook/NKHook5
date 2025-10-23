#include "Play.h"

#include "../../Classes/C_GameSFXManager.h"
#include "../../Classes/eSFX_Items.h"
#include "../../Signatures/Signature.h"

#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Logging;

namespace NKHook5
{
    namespace Patches
    {
        namespace C_GameSFXManager
        {
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t o_func;
            void Play::cb_hook(int audioId) {
				auto* pInstance = reinterpret_cast<Classes::C_GameSFXManager*>(this);
				int16_t audio = *reinterpret_cast<int16_t*>(&audioId);

				Logger::Print("Playing SFX: %hd (%d) (%p)", audio, audioId, audioId);
                // Find the correct audio to play
				for (int i = 0; i < pInstance->mSounds.size(); i++) {
					auto& sound = pInstance->mSounds.at(i);
					auto hash = static_cast<Classes::eSFX_Items>(std::hash<nfw::string>()(sound.mName));
					hash = static_cast<int16_t>(hash) < 0 ? hash : static_cast<Classes::eSFX_Items>(static_cast<int16_t>(hash) * -1);
					Logger::Print("Testing sound: %s (h: %hd)", sound.mName.c_str(), static_cast<int16_t>(hash));
					if (audio == static_cast<int16_t>(hash)) {
						Logger::Print("Found audio hash: %d -> %d", audio, i);
						auto ofn = std::bit_cast<decltype(&Play::cb_hook)>(reinterpret_cast<void*>(o_func));
						(this->*ofn)(i);
						return;
                    }
				}
				auto ofn = std::bit_cast<decltype(&Play::cb_hook)>(reinterpret_cast<void*>(o_func));
				(this->*ofn)(audioId);
            }

            auto Play::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::C_GameSFXManager_Play);
                if(address) {
					PLH::x86Detour* detour = new PLH::x86Detour((const uintptr_t) address, std::bit_cast<size_t>(&Play::cb_hook), &o_func);
                    if(detour->hook()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } // namespace CWeapon
    }
}
