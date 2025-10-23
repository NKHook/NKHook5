#pragma once

#include "../../Classes/Vec2F.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
    namespace Patches
    {
        namespace CEffectTask
        {
            using namespace Classes;

            class FireAt : public IPatch {
				void cb_hook(class CBloon* bloon, Vec2F vecA, Vec2F vecB);
            public:
                FireAt() : IPatch("CEffectTask::FireAt") {}
                auto Apply() -> bool override;
            };
        } // namespace CDGSplashScreen
        
    } // namespace Patches
    
} // namespace NKHook5
