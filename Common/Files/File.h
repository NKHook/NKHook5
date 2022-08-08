#pragma once

#include "IFile.h"

#include <stdint.h>
#include <fstream>
#include <string>
#include <filesystem>

namespace Common {
	namespace Files {
		class File : public IFile {
			std::fstream stream;
			bool writeMode;
		public:
			File();
			File(std::filesystem::path path);
			virtual bool Open(std::filesystem::path) override;
			virtual bool OpenRead(std::filesystem::path);
			virtual bool OpenWrite(std::filesystem::path);
			virtual ~File();
			virtual void Close();
			virtual size_t GetSize() override;
			virtual std::vector<uint8_t> ReadBytes() override;
			virtual void WriteBytes(std::vector<uint8_t> data) override;
			std::string ReadStr();
			void WriteStr(std::string data);
		};
	}
}