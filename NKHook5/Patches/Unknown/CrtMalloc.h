#pragma once

#include "../IPatch.h"

namespace NKHook5 {
	namespace Patches {
		namespace Unknown {
			class CrtMalloc : public IPatch {
			public:
				CrtMalloc() : IPatch("Unknown::CrtMalloc") {}
				auto Apply() -> bool override;
			};
		}
	}
}