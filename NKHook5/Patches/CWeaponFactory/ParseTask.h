#pragma once

#include "../IPatch.h"

namespace NKHook5 {
	namespace Patches {
		namespace CWeaponFactory {
			class ParseTask : public IPatch {
			public:
				ParseTask() : IPatch("CWeaponFactory::ParseTask") {};
				auto Apply() -> bool override;
			};
		}
	}
}