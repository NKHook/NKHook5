#pragma once

#include <filesystem>

namespace NKHook5 {
	namespace Mod {
		class IArchive {
			std::filesystem::path archivePath;
		public:
			IArchive(std::filesystem::path archiveFile);
		};
	}
}