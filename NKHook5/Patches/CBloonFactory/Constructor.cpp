#include "Constructor.h"

#include <Logging/Logger.h>

#include "../../Classes/CBloonFactory.h"
#include "../../Signatures/Signature.h"

NKHook5::Classes::CBloonFactory* g_bloonFactory = nullptr;

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

namespace NKHook5
{
    namespace Patches
    {
        namespace CBloonFactory
        {
            using namespace Signatures;

            static uint64_t o_func;
            Classes::CBloonFactory* __fastcall cb_hook(Classes::CBloonFactory* self)
            {    
                g_bloonFactory = self;
#ifdef _DEBUG
                Print(LogLevel::INFO, "g_bloonFactory: %p", g_bloonFactory);
#endif
                return PLH::FnCast(o_func, &cb_hook)(self);
            }

            auto Constructor::Apply() -> bool
            {
                void* address = Signatures::GetAddressOf(Sigs::CBloonFactory_CCTOR);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
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