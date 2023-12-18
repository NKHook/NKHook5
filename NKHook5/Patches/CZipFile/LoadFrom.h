#pragma once

#include "../../Classes/CZipFile.h"
#include "../IPatch.h"
#include "../../Utils.h"


namespace NKHook5::Patches::CZipFile {
	using namespace NKHook5::Classes;

	class LoadFrom : public IPatch
	{
		Classes::CUnzippedFile* cb_hook(const nfw::string& assetPath, void* param_2, nfw::string& archivePassword);

	public:
		LoadFrom() : IPatch("CZipFile::LoadFrom")
		{

		}
		auto Apply() -> bool override;
	};
}

