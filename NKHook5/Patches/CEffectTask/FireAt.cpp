#include "FireAt.h"

#include "../../Classes/CBloon.h"
#include "../../Classes/CEffectTask.h"
#include "../../Classes/C_GameSFXManager.h"
#include "../../Classes/Vec2F.h"
#include "../../Utils.h"
#include "../../Signatures/Signature.h"

#include <Util/Macro.h>

namespace NKHook5
{
    namespace Patches
    {
        namespace CEffectTask
        {
			using namespace Classes;
            using namespace Signatures;

			static uint64_t o_func;
			void FireAt::cb_hook(class CBloon* bloon, Vec2F vecA, Vec2F vecB) {
				auto* pEffect = reinterpret_cast<Classes::CEffectTask*>(this);
				// If its less than negative 1, its a custom sound
				if (static_cast<int16_t>(pEffect->mAudio) < -1) {
					auto tempAudio = pEffect->mAudio;

					// Reset on instance so the game doesn't play the sound
					pEffect->mAudio = eSFX_Items::NONE;
					auto ofn = std::bit_cast<decltype(&FireAt::cb_hook)>(reinterpret_cast<void*>(o_func));
					(this->*ofn)(bloon, vecA, vecB);

					// Play the sound manually (the hook will convert the hash to the correct value)
					auto inst = C_GameSFXManager::GetInstance();
					inst->Play(static_cast<int16_t>(tempAudio));

					// Restore the audio key
					pEffect->mAudio = tempAudio;

					return;
				}

				auto ofn = std::bit_cast<decltype(&FireAt::cb_hook)>(reinterpret_cast<void*>(o_func));
				(this->*ofn)(bloon, vecA, vecB);
			}

            auto FireAt::Apply() -> bool
            {
				const void* address = Signatures::GetAddressOf(Sigs::CEffectTask_FireAt);
				if (address) {
					auto* detour = new PLH::x86Detour((const uintptr_t) address, std::bit_cast<size_t>(&FireAt::cb_hook), &o_func);
					if (detour->hook()) {
						return true;
					} else {
						return false;
					}
				} else {
					return false;
				}
            }
        }
    }
}
