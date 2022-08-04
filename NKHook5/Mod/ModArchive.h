#pragma once

#include <filesystem>
#include <string>
#include <vector>
#undef min
#undef max
#include <ZipFile.h>

namespace NKHook5 {
	namespace Mod {
		struct ModInfo {
			std::string name;
			std::string description;
			std::string version;
			std::vector<std::string> authors;
			std::string website;
			std::string discord;
			std::string github;
		};

		class ModArchive {
			ModInfo info;
			ZipArchive::Ptr pArchive;
		public:
			ModArchive();
			ModArchive(std::filesystem::path path);
			bool Open(std::filesystem::path path);
			const ModInfo& GetInfo();
		};
	}
}