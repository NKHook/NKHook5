#pragma once

#include <filesystem>
#include <stdint.h>

namespace Common {
	namespace Files {
		class IFile {
			std::filesystem::path path;
			size_t size;
		public:
			IFile();
			IFile(std::filesystem::path path, size_t size);
			virtual bool Open(std::filesystem::path);
			virtual void Close();
			virtual const std::filesystem::path& GetPath();
			virtual size_t GetSize();
			virtual std::vector<uint8_t> ReadBytes();
			virtual void WriteBytes(std::vector<uint8_t> data);
		};
	}
}