#include "Update.h"

#include "../../Classes/CBloon.h"
#include "../../Signatures/Signature.h"

extern uint64_t currentFrame;
int32_t maxBloonUpdates = 0x100;
int32_t bloonPassDenom = 8;

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloon
        {
            using namespace NKHook5;
            using namespace NKHook5::Classes;
            using namespace NKHook5::Patches;
            using namespace NKHook5::Signatures;

            static uint64_t updatesThisFrame = 0;
            static uint64_t lastFrame = currentFrame;
            static uint64_t o_func;
            void Update::cb_hook(float* pSGameTime) {
                if (lastFrame != currentFrame) {
                    lastFrame = currentFrame;
                    updatesThisFrame = 0;
                }
                updatesThisFrame++;
                if (updatesThisFrame > maxBloonUpdates && updatesThisFrame % 2 == 0) {
                    return;
                }

				auto ofn = std::bit_cast<decltype(&Update::cb_hook)>(reinterpret_cast<void*>(o_func));
				(this->*ofn)(pSGameTime);
            }

            auto Update::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CBloon_Update);
                if(address)
                {
                    auto* detour = new PLH::x86Detour((const uintptr_t)address, std::bit_cast<size_t>(&Update::cb_hook), &o_func);
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
        } // namespace CBloon
    }
}
