#pragma once

#include <stdint.h>
#include <fstream>
#include <string>
#include <filesystem>

namespace Common {
	namespace Files {
		class File {
			std::filesystem::path path;
		public:
			File(std::filesystem::path path);
			const std::filesystem::path& GetPath();
			size_t GetSize();
			template<typename T>
			std::vector<T> Read() {
				std::ifstream is(this->path);
				std::istreambuf_iterator<T> start(is), end;
				std::vector<T> result(start, end);
				is.close();
				return result;
			}
			template<typename T>
			void Write(std::vector<T> buffer) {
				std::ofstream os(this->path, std::ios::binary | std::ios::out);
				os.write(buffer.data(), buffer.size() * sizeof(T));
				os.close();
			}
			std::string ReadStr();
			void WriteStr(std::string data);
		};
	}
}