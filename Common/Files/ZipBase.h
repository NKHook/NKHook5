#pragma once

#include "IFile.h"

#include <filesystem>

#undef min
#undef max
#include <ZipFile.h>

namespace Common {
	namespace Files {
		class ZipBase : public IFile {
			ZipArchive::Ptr archive;
			std::string password;
			size_t compressionLevel;
			bool closed;
		public:
			ZipBase();
			ZipBase(std::filesystem::path zipFile, std::string password = "");
			virtual ~ZipBase();
			virtual bool Open(std::filesystem::path path) override;
			virtual void Close() override;
			virtual size_t GetSize() override;
			virtual void SetPassword(std::string password);
			virtual void SetCompressionLevel(size_t level);
			std::vector<std::string> const GetEntries() const;
			virtual std::vector<uint8_t> ReadEntry(std::string entry);
			virtual bool WriteEntry(std::string entry, std::vector<uint8_t> data);
		};
	}
}