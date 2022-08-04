#pragma once

#include "AssetLoader.h"

namespace NKHook5 {
	namespace AssetInjector {
		class ModLoader : public AssetLoader {
			virtual void Initialize();
			virtual Asset* FindInjectedAsset(std::string path);
		};
	}
}