#pragma once

#include "../../Util/NewFramework.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5::Patches::CBaseFileIO
{
	class FileExists : public IPatch
	{
		bool cb_hook(const nfw::string& assetPath, int policy);

	public:
		FileExists() : IPatch("CBaseFileIO::FileExists")
		{

		}
		auto Apply() -> bool override;
	};
}




