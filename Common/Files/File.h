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
			template<typename T>
			std::vector<T> Read() {
				if (this->writeMode) {
					this->Close();
					this->OpenRead(this->GetPath());
				}
				std::istreambuf_iterator<T> start(this->stream), end;
				std::vector<T> result(start, end);
				return result;
			}
			template<typename T>
			void Write(std::vector<T> buffer) {
				if (!this->writeMode) {
					this->Close();
					this->OpenWrite(this->GetPath());
				}
				this->stream.write(buffer.data(), buffer.size() * sizeof(T));
			}
			std::string ReadStr();
			void WriteStr(std::string data);
		};
	}
}