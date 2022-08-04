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
			template<typename T>
			bool ReadEntry(std::string entry, T* buffer) {
				if (this->pArchive == nullptr) {
					printf("Error: pArchive was null");
					return false;
				}
				auto pEntry = this->pArchive->GetEntry(entry);
				if (pEntry == nullptr) {
					printf("Error: pEntry was null");
					return false;
				}
				std::istream* pStream = pEntry->GetDecompressionStream();
				if (pStream == nullptr) {
					printf("Error: pStream was null");
					return false;
				}
				*buffer = T(std::istreambuf_iterator<char>(*pStream), {});
				return true;
			}
		};
	}
}