#pragma once

#include "../IPatch.h"

namespace NKHook5 {
	namespace Patches {
		namespace Unknown {
            class WinMain : public IPatch
            {
            public:
                WinMain() : IPatch("Unknown::WinMain")
                {

                }
                auto Apply() -> bool override;
            };
		}
	}
}