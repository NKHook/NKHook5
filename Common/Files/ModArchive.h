#pragma once

#include "ZipBase.h"
#include <Mod/ModInfo.h>

#include <filesystem>
#include <string>
#include <vector>

namespace Common {
	namespace Files {
		using namespace Mod;

		class ModArchive : public ZipBase {
			ModInfo info;
		public:
			ModArchive();
			virtual bool Open(std::filesystem::path path) override;
			virtual bool OpenRead(std::filesystem::path path);
			virtual bool OpenWrite(std::filesystem::path path);
			ModArchive(std::filesystem::path path);
			const ModInfo& const GetInfo() const;
			void SetInfo(ModInfo);
		};
	}
}