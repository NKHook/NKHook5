#pragma once

#include "MemAsset.h"

namespace NKHook5 {
	namespace AssetInjector {
		class ModdedAsset : public MemAsset {
		public:
			ModdedAsset(std::string path);
			virtual bool ExpectsMerge();
		};
	}
}