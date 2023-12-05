#pragma once

#include "IFile.h"

#include <filesystem>

#include <ZipFile.h>

namespace Common::Files {
	class ZipBase : public IFile {
		ZipArchive::Ptr archive;
		std::string password;
		size_t compressionLevel;
		bool closed;
	public:
		ZipBase();
		explicit ZipBase(std::filesystem::path zipFile, std::string password = "");
		virtual ~ZipBase();
		bool Open(std::filesystem::path path) override;
		void Close() override;
		[[nodiscard]] size_t GetSize() const override;
		virtual void SetPassword(const std::string& password);
		virtual void SetCompressionLevel(size_t level);
		[[nodiscard]] std::vector<std::string> GetEntries() const;
		[[nodiscard]] bool HasEntry(const std::string& entry) const;
		virtual std::vector<uint8_t> ReadEntry(const std::string& entry);
		virtual bool WriteEntry(std::string entry, std::vector<uint8_t> data);
	};
}