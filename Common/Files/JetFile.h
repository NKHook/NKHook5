#pragma once

#include "ZipBase.h"

#include <filesystem>

#define JET_PASSWORD "Q%_{6#Px]]"
#define JET_COMPRESS_LEVEL 1

namespace Common {
	namespace Files {
		class JetFile : public ZipBase {
		public:
			JetFile();
			JetFile(std::filesystem::path path);
			virtual bool Open(std::filesystem::path path) override;
		};
	}
}