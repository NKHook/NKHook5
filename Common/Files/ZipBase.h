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
		public:
			ZipBase();
			ZipBase(std::filesystem::path zipFile, std::string password = "");
			virtual bool Open(std::filesystem::path path) override;
			virtual void Close() override;
			virtual size_t GetSize() override;
			virtual void SetPassword(std::string password);
			virtual void SetCompressionLevel(size_t level);
			std::vector<std::string> const GetEntries() const;
			template<typename T>
			bool const ReadEntry(std::string entry, T* buffer) const {
				if (this->archive == nullptr) {
					printf("Error: pArchive was null in read");
					return false;
				}
				auto pEntry = this->archive->GetEntry(entry);
				if (pEntry == nullptr) {
					printf("Error: pEntry was null in read\n");
					printf("Entry: %s\n", entry.c_str());
					return false;
				}
				pEntry->SetPassword(this->password);
				std::istream* pStream = pEntry->GetDecompressionStream();
				if (pStream == nullptr) {
					printf("Error: pStream was null in read\n");
					printf("Entry: %s\n", entry.c_str());
					return false;
				}
				*buffer = T(std::istreambuf_iterator<char>(*pStream), {});
				return true;
			}

			template<typename T>
			bool WriteEntry(std::string entry, T* buffer, size_t len) {
				if (this->archive == nullptr) {
					printf("Error: pArchive was null in write");
					return false;
				}
				ZipArchiveEntry::Ptr pEntry = this->archive->GetEntry(entry);
				if (pEntry == nullptr) {
					pEntry = this->archive->CreateEntry(entry);
				}
				std::ostream writeStream;
				writeStream.write(buffer, len);
				DeflateMethod::Ptr method = DeflateMethod::Create();
				method->SetCompressionLevel(this->compressionLevel);
				pEntry->SetPassword(this->password);
				pEntry->SetCompressionStream(writeStream, method, ZipArchiveEntry::CompressionMode::Immediate);
				return true;
			}
		};
	}
}