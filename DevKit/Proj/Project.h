#pragma once

#include <Mod/ModInfo.h>

#include <filesystem>
#include <string>

namespace DevKit {
	namespace Proj {
		using namespace Common::Mod;
		namespace fs = std::filesystem;

		class Project {
			fs::path path;
			ModInfo info;
			fs::path modInfoPath;
			fs::path vanillaAssetsPath;
			fs::path modAssetsPath;
		public:
			Project();
			Project(fs::path path);
			bool Open(fs::path path);
			fs::path GetModInfoPath();
			fs::path GetVanillaPath();
			fs::path GetModPath();
			const ModInfo& GetInfo();
		};
	}
}