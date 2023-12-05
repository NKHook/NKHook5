#pragma once

#include "ZipBase.h"
#include <Mod/ModInfo.h>

#include <filesystem>
#include <string>
#include <vector>

namespace Common::Files {
	using namespace Mod;

	class ModArchive : public ZipBase {
		ModInfo info;
	public:
		ModArchive();
		bool Open(std::filesystem::path path) override;
		virtual bool OpenRead(std::filesystem::path path);
		virtual bool OpenWrite(std::filesystem::path path);
		explicit ModArchive(std::filesystem::path path);
		[[nodiscard]] const ModInfo& GetInfo() const;
		void SetInfo(ModInfo);
	};
}