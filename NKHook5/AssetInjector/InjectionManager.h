#pragma once

#include "Asset.h"
#include "AssetLoader.h"
#include <string>

namespace NKHook5 {
	namespace AssetInjector {
		namespace InjectionManager {
			void SetupAssetLoader();
			AssetLoader* GetLoader();
		}
	}
}