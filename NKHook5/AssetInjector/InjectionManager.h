#pragma once

#include "Asset.h"
#include <string>

namespace NKHook5 {
	namespace AssetInjector {
		namespace InjectionManager {
			void Initialize();
			Asset* FindInjectedAsset(std::string path);
		}
	}
}