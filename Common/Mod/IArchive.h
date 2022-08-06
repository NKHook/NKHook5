#pragma once

#include <filesystem>

namespace Common {
	namespace Mod {
		class IArchive {
			std::filesystem::path archivePath;
		public:
			IArchive(std::filesystem::path archiveFile);
		};
	}
}